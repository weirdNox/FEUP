package dkeep.cli;

import dkeep.logic.*;
import java.util.Scanner;

public class Main {
    
	public static void main(String[] args) {
		GameState state = new GameState();
		state.draw();
		
		Scanner scanner = new Scanner(System.in);
		
		gameLoop:
		for(;;) {
			Input input = Input.up;
			
			System.out.print("Input: ");
			for(;;) {
				String inputStr = scanner.nextLine();
				char direction = inputStr.charAt(0);
				
				boolean hasInput = true;
				
				switch(direction) {
				case 'w': {
					input = Input.up;
				} break;

				case 'a': {
					input = Input.left;
				} break;

				case 's': {
					input = Input.down;
				} break;

				case 'd': {
					input = Input.right;
				} break;
				
				case 'q': {
					break gameLoop;
				} 
				
				default: {
					hasInput = false;
				} break;
				}
				
				if(hasInput) {
					break;
				}
			}
			
			state.tick(input);
			
			if(state.done) {
				break;
			}
		}
		scanner.close();
	}
}
