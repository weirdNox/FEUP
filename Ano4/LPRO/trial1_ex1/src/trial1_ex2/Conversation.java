package trial1_ex2;

import java.util.ArrayList;
import java.util.HashSet;

public class Conversation {
	HashSet<String> map = new HashSet<String>();
	ArrayList<IdentifiedMessage> msgs = new ArrayList<IdentifiedMessage>();
	
	int max = 0;

	public Conversation(int i) {
		max = i;
	}

	public int getMaxNumberOfUsers() {
		return max;
	}

	public int getUserCount() {
		return map.size();
	}

	public void addUser(String string) {
		if(getUserCount() < max) {
			if(!map.contains(string)) {
				map.add(string);
			}
		}
	}

	public void addMessage(IdentifiedMessage identifiedMessage) {
		String user = identifiedMessage.getUser();
		if(map.contains(user)) {
			msgs.add(identifiedMessage);
		}
	}

	public int getMessageCount() {
		return msgs.size();
	}

	public void removeUser(String string) {
		map.remove(string);
	}

	public ArrayList<Message> getUserMessages(String user) {
		ArrayList<Message> result = new ArrayList<Message>();
		for(IdentifiedMessage msg : msgs) {
			if(msg.user == user) {
				result.add(msg);
			}
		}
		return result;
	}

}
