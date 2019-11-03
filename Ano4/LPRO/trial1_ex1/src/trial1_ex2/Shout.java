package trial1_ex2;

public class Shout extends MessageFormatter {

	@Override
	public String format(String msg) {
		return msg.toUpperCase();
	}

}
