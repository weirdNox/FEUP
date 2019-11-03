package trial1_ex2;

public class Message implements Comparable<Message> {
	String message;
	MessageFormatter mf = null;

	public Message(String s) {
		message = s;
	}

	public Message(Message m) {
		this.mf = m.mf;
		message = m.message;
	}

	public Object getMessage() {
		if(mf != null) {
			return mf.format(message);
		}
		return message;
	}

	public void setMessage(String s) {
		message = s;
	}

	public void setFormattingStrategy(MessageFormatter mf) {
		this.mf = mf;
	}
	
	public boolean equals(Object o) {
		if(o instanceof Message) {
			Message om = (Message)o;
			return om.message.equals(this.message);
		}
		return false; 
	}
	
	public String toString() {
		return "msg:[" + message + "]";
	}

	@Override
	public int compareTo(Message arg0) {
		return message.compareTo(arg0.message);
	}

}
