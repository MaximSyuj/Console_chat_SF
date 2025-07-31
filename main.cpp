#include "Chat.h"

int main()
{
	Chat chat;

	chat.run();

	while (chat.chatRun())
	{
		chat.mainMenu();

		while (chat.getCurrentUser())
		{
			chat.userMenu();
		}
	}

	return 0;
}