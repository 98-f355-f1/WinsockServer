#include "Server.h"

void ServerCommandHandler(Server *listener, SOCKET clientSock, std::string message);

void adminCommand(std::string arguments, SOCKET clientSock, Server *listener);
void awayCommand(std::string arguments, SOCKET clientSock, Server *listener);
void channelCommand(std::string arguments, SOCKET clientSock, Server *listener);
void cnoticeCommand(std::string arguments, SOCKET clientSock, Server *listener);
void connectCommand(std::string arguments, SOCKET clientSock, Server *listener);
void cprivmsgCommand(std::string arguments, SOCKET clientSock, Server *listener);
void dieCommand(std::string arguments, SOCKET clientSock, Server *listener);
void encapCommand(std::string arguments, SOCKET clientSock, Server *listener);
void errorCommand(std::string arguments, SOCKET clientSock, Server *listener);
void helpCommand(std::string arguments, SOCKET clientSock, Server *listener);
void infoCommand(std::string arguments, SOCKET clientSock, Server *listener);
void inviteCommand(std::string arguments, SOCKET clientSock, Server *listener);
void isonCommand(std::string arguments, SOCKET clientSock, Server *listener);
void kickCommand(std::string arguments, SOCKET clientSock, Server *listener);
void killCommand(std::string arguments, SOCKET clientSock, Server *listener);
void knockCommand(std::string arguments, SOCKET clientSock, Server *listener);
void linksCommand(std::string arguments, SOCKET clientSock, Server *listener);
void listCommand(std::string arguments, SOCKET clientSock, Server *listener);
void lusersCommand(std::string arguments, SOCKET clientSock, Server *listener);
void modeCommand(std::string arguments, SOCKET clientSock, Server *listener);
void modtCommand(std::string arguments, SOCKET clientSock, Server *listener);
void namesCommand(std::string arguments, SOCKET clientSock, Server *listener);
void namesxCommand(std::string arguments, SOCKET clientSock, Server *listener);
void nickCommand(std::string arguments, SOCKET clientSock, Server *listener);
void noticeCommand(std::string arguments, SOCKET clientSock, Server *listener);
void operCommand(std::string arguments, SOCKET clientSock, Server *listener);
void partCommand(std::string arguments, SOCKET clientSock, Server *listener);
void passCommand(std::string arguments, SOCKET clientSock, Server *listener);
void pingCommand(std::string arguments, SOCKET clientSock, Server *listener);
void pongCommand(std::string arguments, SOCKET clientSock, Server *listener);
void privmsgCommand(std::string arguments, SOCKET clientSock, Server *listener);
void quitCommand(std::string arguments, SOCKET clientSock, Server *listener);
void rehashCommand(std::string arguments, SOCKET clientSock, Server *listener);
void restartCommand(std::string arguments, SOCKET clientSock, Server *listener);
void rulesCommand(std::string arguments, SOCKET clientSock, Server *listener);
void serverCommand(std::string arguments, SOCKET clientSock, Server *listener);
void serviceCommand(std::string arguments, SOCKET clientSock, Server *listener);
void servlistCommand(std::string arguments, SOCKET clientSock, Server *listener);
void setnameCommand(std::string arguments, SOCKET clientSock, Server *listener);
void shitCommand(std::string arguments, SOCKET clientSock, Server *listener);
void silenceCommand(std::string arguments, SOCKET clientSock, Server *listener);
void squeryCommand(std::string arguments, SOCKET clientSock, Server *listener);
void squitCommand(std::string arguments, SOCKET clientSock, Server *listener);
void summonCommand(std::string arguments, SOCKET clientSock, Server *listener);
void timeCommand(std::string arguments, SOCKET clientSock, Server *listener);
void topicCommand(std::string arguments, SOCKET clientSock, Server *listener);
void traceCommand(std::string arguments, SOCKET clientSock, Server *listener);
void userCommand(std::string arguments, SOCKET clientSock, Server *listener);
void userhostCommand(std::string arguments, SOCKET clientSock, Server *listener);
void useripCommand(std::string arguments, SOCKET clientSock, Server *listener);
void usersCommand(std::string arguments, SOCKET clientSock, Server *listener);
void versionCommand(std::string arguments, SOCKET clientSock, Server *listener);
void wallopsCommand(std::string arguments, SOCKET clientSock, Server *listener);
void watchCommand(std::string arguments, SOCKET clientSock, Server *listener);
void whoCommand(std::string arguments, SOCKET clientSock, Server *listener);
void whoisCommand(std::string arguments, SOCKET clientSock, Server *listener);
void whowasCommand(std::string arguments, SOCKET clientSock, Server *listener);

class CommandHandler
{
public:


	bool AddCommand(std::string name, int argCount, SOCKET clientSock, void(*handler)(std::string /*params*/, SOCKET /*clientSock*/, Server* /*listener*/))
	{
		CommandEntry entry;
		entry.argCount = argCount;
		entry.clientSocket = clientSock;
		entry.handler = handler;
		std::transform(name.begin(), name.end(), name.begin(), towlower);
		_commands.insert(std::pair<std::string, CommandEntry>(name, entry));
		return true;
	}

	void ParseCommand(std::string command, SOCKET clientSock, Server *listener)
	{
		if (_commands.empty())
		{
			std::cout << "No commands available." << std::endl;
			return;
		}

		if (command[0] == '/') {
			command = command.substr(1);
		}

		std::string name = command.substr(0, command.size() - 2);
		name = name.substr(0, name.find(" "));
		std::string args = name.substr(name.find(" ") + 1);
		int argCount = std::count(args.begin(), args.end(), ' ');

		std::transform(name.begin(), name.end(), name.begin(), towlower);

		std::unordered_map<std::string, CommandEntry>::const_iterator itr = _commands.find(name);
		if (itr == _commands.end())
		{
			// send back to chatter
			std::cout << "Command not found" << std::endl;
			return;
		}

		if (++argCount < itr->second.argCount)
		{
			// send back to chatter
			std::cout << "Insuficient arguments. . ." << std::endl;
			return;
		}

		(*(itr->second.handler))(args, clientSock, listener);;
	}

private:
	struct CommandEntry
	{
		int argCount;
		SOCKET clientSocket;
		void(*handler)(std::string /*arguments*/, SOCKET /*clientSock*/, Server* /*listener*/);
	};

	std::unordered_map<std::string, CommandEntry> _commands;
};