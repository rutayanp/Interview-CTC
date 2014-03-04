from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor
from twisted.internet.endpoints import TCP4ServerEndpoint

class Chat (LineReceiver) :

    def __init__(self, users, chat, hottub):
        self.users = users
        self.name = None
        self.state = "GETNAME"
        self.chat = chat
        self.hottub = hottub

    def connectionMade(self):
        self.sendLine("<= Hola!! Lets Talk! ")
        self.sendNext("<= what would be your name?")

    def connectionLost(self, reason):
        if self.name in self.users:
            del self.users[self.name]

    def lineReceived(self, line):
        if self.state == "GETNAME":
            self.handle_GETNAME(line)
        elif self.state == "SHOW":
            self.show_ROOM(line)
        elif self.state == "ROOM":
            self.handle_ROOM(line)
        else:
            self.handle_CHAT(line)
    
    def show_ROOM(self, message):
        if message == "/rooms" or message == "/room":
            self.sendLine("<= Active Rooms are: ")
            self.sendLine("<= * chat(%d)" % len(self.chat))
            self.sendLine("<= * hottub(%d)" % len(self.hottub))
            self.sendNext("<= End of List ")
            self.state = "ROOM"
        else:
            self.sendNext("<= * Please select a room --> use /rooms")
            self.state = "SHOW"

    def handle_ROOM(self, message):
        commands = message.split()
        if len(commands) == 2:
            print "%s joined %s" % (self.name,commands[1])
            command = commands[0]
            room = commands[1]
        else: 
            return
        if command.lower() == "/join":
            if not room:
                self.sendNext("<= Please provide a room")
            elif room != "chat" and room !="hottub":
                self.sendNext("<= Please provide a valid room")
            else:
                self.sendLine("<= Entering room: " + room)
                
                if room.lower() == "chat":
                    self.chat[self.name] = self
                    
                    for name in self.chat:
                        if(name == self.name):
                            self.sendLine("<= *" + name + " (** this is you)")
                        else:
                            self.sendLine("<= *" + name)
                else:
                    self.hottub[self.name] = self
                    for name in self.hottub:
                        if(name == self.name):
                            self.sendLine("<= *" + name + " (** this is you)")
                        else:
                            self.sendLine("<= *" + name)

                self.sendNext("<= End of list")
                self.state = "CHAT"
        else:
            self.sendNext("<= You need to join a room first buddy! this is how --> /join <room name>")
        self.state = "CHAT"     

    def handle_GETNAME(self, name):
        if name in self.users:
            self.sendNext("<= Name Taken, please choose another.")
            return
        self.sendNext("<= Welcome, %s!" % (name,))
        self.name = name
        self.users[name] = self
        self.state = "SHOW"

    def handle_CHAT(self, message):
        message = "<%s> %s" % (self.name, message)
        self.sendNext("")
        for name, protocol in self.users.iteritems():
            if protocol != self:
                protocol.sendNext(message)

    def sendNext(self, line):
        self.transport.write(line + "\n=> ")

class ChatFactory(Factory):

    def __init__(self):
        self.users = {}
        self.chat = {}
        self.hottub = {}

    def buildProtocol(self, addr):
        return Chat(self.users, self.chat, self.hottub)

#endpoint = TCP4ServerEndpoint(reactor, 8007)
#endpoint.listen(ChatFactory())
reactor.listenTCP(9111, ChatFactory(), 10, '0.0.0.0' )
reactor.run()
