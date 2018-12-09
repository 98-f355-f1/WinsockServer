#include "CommandHandler.h"
#include "Channels.h"
#include "Server.h"

Commands commands{ "commands.txt" };
Quotd quotd{ "quotes.txt" };
Channels channelList{ "channels.txt" };
CommandHandler commandHandler;

void msgCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	std::string to = arguments.substr(0, arguments.find(" "));
	std::string text = arguments.substr(arguments.find(" ") + 1);

	std::cout << "To " + to + ": " + text << std::endl;
	std::string msg = "PRIVMSG " + to + " :" + text + "\r\n";
	listener->sendMsg(clientSock, msg);
};

void joinCommand(std::string channel, SOCKET clientSock, Server *listener)
{
	std::string cmd = channel.substr(0, channel.find(" "));
	std::string chnl = channel.substr(channel.find(" ") + 1);
	std::cout << chnl << std::endl;
	auto it = std::find(channelList.channels.begin(),
						channelList.channels.end(),
						chnl);

	std::cout << chnl << std::endl;

	if (it != channelList.channels.end())
	{
		std::cout << *it << std::endl;
		std::string msg = "You have JOIN(ed) " + chnl + "\r\n";
		listener->sendMsg(clientSock, msg);
	}
	else
	{
		std::cout << chnl << std::endl;
		channelList.addChannel(chnl);
		std::string msg = "You have added and JOIN(ed) " + chnl + "\r\n";
		listener->sendMsg(clientSock, msg);
	}
}

void partCommand(std::string channel, SOCKET clientSock, Server *listener)
{
	if (channel[0] != '#')
		channel = "#" + channel;

	std::string msg = "PART " + channel + "\r\n";
	listener->sendMsg(clientSock, msg);
}

void ctcpCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	std::string to = arguments.substr(0, arguments.find(" "));
	std::string text = arguments.substr(arguments.find(" ") + 1);

	std::transform(text.begin(), text.end(), text.begin(), towupper);
	std::string msg = "PRIVMSG " + to + " :\001" + text + "\001\r\n";
	listener->sendMsg(clientSock, msg);
}

void adminCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/admin\r\n");
}

void awayCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/away\r\n");
}

void channelCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	joinCommand(arguments, clientSock, listener);
	//listener->sendMsg(clientSock, "/channels\r\n");
}

void cnoticeCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/cnotice\r\n");
}

void connectCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/connect\r\n");
}

void cprivmsgCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/cprivmsg\r\n");
}

void dieCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/die\r\n");
}

void encapCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/encap\r\n");
}

void errorCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/error\r\n");
}

void exitCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/quit\r\n");
}

void helpCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/help\r\n");
}

void infoCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/info\r\n");
}

void inviteCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/invite\r\n");
}

void isonCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/ison\r\n");
}

void kickCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/kick\r\n");
}

void killCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/kill\r\n");
}

void knockCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/knock\r\n");
}

void linksCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/links\r\n");
}

void listCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	std::string msg = "Current list of channels:\r\n";

	for (auto c : channelList.getChannels())
	{
		msg.append(" " + c + "\r\n");
	}
	listener->sendMsg(clientSock, msg);
}

void lusersCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/lusers\r\n");
}

void modeCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/mode\r\n");
}

void modtCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/modt\r\n");
}

void namesCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/names\r\n");
}

void namesxCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/namesx\r\n");
}

void nickCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/nick\r\n");
}

void noticeCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/notice\r\n");
}

void operCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/oper\r\n");
}

//void partCommand(std::string arguments, SOCKET clientSock, Server *listener)
//{
//	arguments = "";
//	listener->sendMsg(clientSock, "/part");
//}

void passCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/pass\r\n");
}

void pingCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	std::string msg = "PING\r\n";
	listener->sendMsg(clientSock, msg);
}

void pongCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	std::string msg = "PONG\r\n";
	listener->sendMsg(clientSock, msg);
}

void privmsgCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/privmsg\r\n");
}

void quitCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/quit\r\n");
}

void quoteCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	std::string quote = quotd.getRandomQuote() + "\r\n";
	if (listener->sendMsg(clientSock, quote) == SOCKET_ERROR)
	{
		cout << "Send failed: " << WSAGetLastError() << endl;
	}
}

void rehashCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/rehash\r\n");
}

void restartCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/restart\r\n");
}

void rulesCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/rules\r\n");
}

void serverCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/server\r\n");
}

void serviceCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/service\r\n");
}

void servlistCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/servlist\r\n");
}

void setnameCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/setname\r\n");
}

void shitCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/shit\r\n");
}

void silenceCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/silence\r\n");
}

void squeryCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/squery\r\n");
}

void squitCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/squit\r\n");
}

void summonCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/summon\r\n");
}

void timeCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/time\r\n");
}

void topicCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/topic\r\n");
}

void traceCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/trace\r\n");
}

void userCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/user\r\n");
}

void userhostCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/userhost\r\n");
}

void useripCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/userip\r\n");
}

void usersCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/users\r\n");
}

void versionCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/version\r\n");
}

void wallopsCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/wallops\r\n");
}

void watchCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/watch\r\n");
}

void whoCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/who\r\n");
}

void whoisCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/whois\r\n");
}

void whowasCommand(std::string arguments, SOCKET clientSock, Server *listener)
{
	arguments = "";
	listener->sendMsg(clientSock, "/whowas\r\n");
}

void ServerCommandHandler(Server *listener, SOCKET clientSock, std::string message)
{
	commandHandler.AddCommand("msg", 2, clientSock, &msgCommand);
	commandHandler.AddCommand("join", 1, clientSock, &joinCommand);
	commandHandler.AddCommand("part", 1, clientSock, &partCommand);
	commandHandler.AddCommand("ctcp", 2, clientSock, &ctcpCommand);
	commandHandler.AddCommand("quote", 0, clientSock, &quoteCommand);
	commandHandler.AddCommand("admin", 0, clientSock, &adminCommand);
	commandHandler.AddCommand("away", 0, clientSock, &awayCommand);
	commandHandler.AddCommand("channel", 0, clientSock, &channelCommand);
	commandHandler.AddCommand("cnotice", 0, clientSock, &cnoticeCommand);
	commandHandler.AddCommand("connect", 0, clientSock, &connectCommand);
	commandHandler.AddCommand("cprivmsg", 0, clientSock, &cprivmsgCommand);
	commandHandler.AddCommand("die", 0, clientSock, &dieCommand);
	commandHandler.AddCommand("encap", 0, clientSock, &encapCommand);
	commandHandler.AddCommand("error", 0, clientSock, &errorCommand);
	//commandHandler.AddCommand("exit", 0, clientSock, &exitCommand);
	commandHandler.AddCommand("help", 0, clientSock, &helpCommand);
	commandHandler.AddCommand("info", 0, clientSock, &infoCommand);
	commandHandler.AddCommand("invite", 0, clientSock, &inviteCommand);
	commandHandler.AddCommand("ison", 0, clientSock, &isonCommand);
	commandHandler.AddCommand("kick", 0, clientSock, &kickCommand);
	commandHandler.AddCommand("kill", 0, clientSock, &killCommand);
	commandHandler.AddCommand("knock", 0, clientSock, &knockCommand);
	commandHandler.AddCommand("links", 0, clientSock, &linksCommand);
	commandHandler.AddCommand("list", 0, clientSock, &listCommand);
	commandHandler.AddCommand("lusers", 0, clientSock, &lusersCommand);
	commandHandler.AddCommand("mode", 0, clientSock, &modeCommand);
	commandHandler.AddCommand("modt", 0, clientSock, &modtCommand);
	commandHandler.AddCommand("names", 0, clientSock, &namesCommand);
	commandHandler.AddCommand("namesx", 0, clientSock, &namesxCommand);
	commandHandler.AddCommand("nick", 0, clientSock, &nickCommand);
	commandHandler.AddCommand("notice", 0, clientSock, &noticeCommand);
	commandHandler.AddCommand("oper", 0, clientSock, &operCommand);
	commandHandler.AddCommand("part", 0, clientSock, &partCommand);
	commandHandler.AddCommand("pass", 0, clientSock, &passCommand);
	commandHandler.AddCommand("ping", 0, clientSock, &pingCommand);
	commandHandler.AddCommand("pong", 0, clientSock, &pongCommand);
	commandHandler.AddCommand("privmsg", 0, clientSock, &privmsgCommand);
	//commandHandler.AddCommand("quit", 0, clientSock, &quitCommand);
	commandHandler.AddCommand("rehash", 0, clientSock, &rehashCommand);
	commandHandler.AddCommand("restart", 0, clientSock, &restartCommand);
	commandHandler.AddCommand("rules", 0, clientSock, &rulesCommand);
	commandHandler.AddCommand("server", 0, clientSock, &serverCommand);
	commandHandler.AddCommand("service", 0, clientSock, &serviceCommand);
	commandHandler.AddCommand("servlist", 0, clientSock, &servlistCommand);
	commandHandler.AddCommand("setname", 0, clientSock, &setnameCommand);
	commandHandler.AddCommand("shit", 0, clientSock, &shitCommand);
	commandHandler.AddCommand("silence", 0, clientSock, &silenceCommand);
	commandHandler.AddCommand("squery", 0, clientSock, &squeryCommand);
	commandHandler.AddCommand("squit", 0, clientSock, &squitCommand);
	commandHandler.AddCommand("summon", 0, clientSock, &summonCommand);
	commandHandler.AddCommand("time", 0, clientSock, &timeCommand);
	commandHandler.AddCommand("topic", 0, clientSock, &topicCommand);
	commandHandler.AddCommand("trace", 0, clientSock, &traceCommand);
	commandHandler.AddCommand("user", 0, clientSock, &userCommand);
	commandHandler.AddCommand("userhost", 0, clientSock, &userhostCommand);
	commandHandler.AddCommand("userip", 0, clientSock, &useripCommand);
	commandHandler.AddCommand("users", 0, clientSock, &usersCommand);
	commandHandler.AddCommand("version", 0, clientSock, &versionCommand);
	commandHandler.AddCommand("wallops", 0, clientSock, &wallopsCommand);
	commandHandler.AddCommand("watch", 0, clientSock, &watchCommand);
	commandHandler.AddCommand("who", 0, clientSock, &whoCommand);
	commandHandler.AddCommand("whois", 0, clientSock, &whoisCommand);
	commandHandler.AddCommand("whowas", 0, clientSock, &whowasCommand);

	if (message.substr(0, 1) == "/") {
		commandHandler.ParseCommand(message, clientSock, (Server*)listener);
	}
	else {
		if (listener->sendMsg(clientSock, message) == SOCKET_ERROR)
		{
			cout << "Send failed: " << WSAGetLastError() << endl;
		}
	}
}
