package trial1_ex2;

public class Capitalize extends MessageFormatter {
	@Override
	public String format(String msg) {
		char[] arr = msg.toCharArray();
		boolean capitalize = true;
		for(int idx = 0; idx < arr.length; idx++) {
			char a = arr[idx];
			if(a == ' ') {
				capitalize = true;
			}
			else if(capitalize && a >= 'a' && (a - 'a') <= ('z'-'a')) {
				arr[idx] = (char) ((a - 'a') + 'A');
				capitalize = false;
			}
		}
		
		return String.copyValueOf(arr);
	}
}
