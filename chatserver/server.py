from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor
from twisted.internet.endpoints import TCP4ServerEndpoint

class Chat (LineReceiver) :
    count = 32

    def __init__(self, users, chat, hottub):
        self.users = users
        self.name = None
        self.state = "GETNAME"
        self.chat = chat
        self.hottub = hottub
        Chat.count += 1
        self.color = Chat.count
        self.room = ''

    def connectionMade(self):
        self.sendLine("<= Hola!! Lets Talk! ")
        self.sendNext("<= what would be your name?")

    def connectionLost(self, reason):
        if self.name in self.users:
            del self.users[self.name]


    def lineReceived(self, line):
        if line == "/quit":
            self.sendLine("<= BYE")
            self.connectionLost(self, "Connection closed by foreign host.")
        if self.state == "GETNAME":
            self.handle_GETNAME(line)
        elif self.state == "SHOW":
            self.show_ROOM(line)
        elif self.state == "ROOM":
            self.handle_ROOM(line)
        else:
            self.handle_CHAT(line)
    
    def show_ROOM(self, message):
        print "%s -- %s" % (self.name, message)
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
            print "%s joined %s" % (self.colorName(self.name),commands[1])
            command = commands[0]
            room = commands[1]
            self.room = room
        else: 
            self.sendNext("<= You need to join a room first buddy! this is how --> /join <room name>")
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
                
                    for name,protocol in self.chat.iteritems():
                        if(name != self.name):
                            protocol.sendNext("\n<= *new user joined chat: " + self.colorName(self.name)) #new line to move the prompt to next line 

                    for name, protocol in self.chat.iteritems():
                        if(name == self.name):
                            self.sendLine("<= *" + protocol.colorName(name) + " (** this is you)")
                        else:
                            self.sendLine("<= *" + protocol.colorName(name))
                else:
                    self.hottub[self.name] = self
                    
                    for name,protocol in self.hottub.iteritems():
                        if(name != self.name):
                            protocol.sendNext("\n<= *new user joined chat: " + self.colorName(self.name)) #new line to move the prompt to next line 
                    for name, protocol in self.hottub.iteritems():
                        if(name == self.name):
                            self.sendLine("<= *" + protocol.colorName(name) + " (** this is you)")
                        else:
                            self.sendLine("<= *" + protocol.colorName(name))

                self.sendNext("<= End of list")
                self.state = "CHAT"
                return
        else:
            self.sendNext("<= You need to join a room first buddy! this is how --> /join <room name>")
        self.state = "ROOM"     

    def handle_GETNAME(self, name):
        if name in self.users:
            self.sendNext("<= Name Taken, please choose another.")
            return
        self.sendNext("<= Welcome, %s!" % (self.colorName(name),))
        self.name = name
        self.users[name] = self
        self.state = "SHOW"

    def handle_CHAT(self, line):

        message = "<= %s: %s" % (self.colorName(self.name), line)
        
        if(self.room == "chat"):
            allmembers = self.chat
        else:
            allmembers = self.hottub
        
        if(line == "/leave"):
            print "%s leaving !\n" % self.name
            for name,protocol in allmembers.iteritems():
                if(name != self.name):
                    protocol.sendNext("\n<= *user has left" + self.room + ": " + self.colorName(self.name)) 
                else:   
                    protocol.sendNext("<= *user has left" + self.room + ": " + self.colorName(self.name) + "(**this is you)")
            if (self.name in self.chat):
                del self.chat[self.name]
            if (self.name in self.hottub):
                del self.hottub[self.name]
            allmembers.pop(self.name, None)
            self.state = "SHOW"
            return
 
        for name, protocol in allmembers.iteritems():
            if(name != self.name):
                protocol.sendNext("\n" + message)
            else:
                protocol.sendNext(message)

    def sendNext(self, line):
        self.transport.write(line + "\n=> ")

    def colorName(self, name):
        return "\033[1;%sm%s\033[0m" % (str(self.color), name)

class ChatFactory(Factory):

    def __init__(self):
        self.users = {}
        self.chat = {}
        self.hottub = {}

    def buildProtocol(self, addr):
        return Chat(self.users, self.chat, self.hottub)

reactor.listenTCP(9111, ChatFactory(), 10, '0.0.0.0' )
reactor.run()
