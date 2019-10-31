package miniquest1;

import java.util.Scanner;
import java.util.Random;

public class Miniquest1 {

	public static boolean hasKey = false;
	public static boolean victory = false;

	public static void printMap(char [][] map) {
		for(int y = 0; y < map.length; ++y) {
			for(int x = 0; x < map[y].length; ++x) {
				System.out.print(map[y][x]);
			}
			System.out.print('\n');
		}
	}

	public static boolean checkProximityToDragon(char [][] map) {
		int heroX = 0, heroY = 0;

		searchLoop:
		for(int y = 0; y < map.length; ++y) {
			for(int x = 0; x < map[y].length; ++x) {
				if(map[y][x] == 'H') {
					heroX = x;
					heroY = y;
					break searchLoop;
				}
			}
		}

		if((heroX > 0 && map[heroY][heroX-1] == 'D') ||
				(heroY > 0 && map[heroY-1][heroX] == 'D') ||
				(heroX < map[heroY].length-1 && map[heroY][heroX+1] == 'D') ||
				(heroY < map.length-1 && map[heroY+1][heroX] == 'D'))
		{
			return true;
		}

		return false;
	}

	public static void walk(char[][] map, int diffX, int diffY) {
		int heroX = 0, heroY = 0;

		searchLoop:
		for(int y = 0; y < map.length; ++y) {
			for(int x = 0; x < map[y].length; ++x) {
				if(map[y][x] == 'H') {
					heroX = x;
					heroY = y;
					break searchLoop;
				}
			}
		}

		int newHeroX = heroX + diffX;
		int newHeroY = heroY + diffY;
		if(newHeroY >= 0 && newHeroY < map.length && newHeroX >= 0 && newHeroX < map[newHeroY].length) {
			char nextTile = map[newHeroY][newHeroX];
			if(nextTile == ' ') {
				map[heroY][heroX] = ' ';
				map[newHeroY][newHeroX] = 'H';
			}
			else if(nextTile == 'K') {
				map[heroY][heroX] = ' ';
				map[newHeroY][newHeroX] = 'H';
				hasKey = true;
			}
			else if(nextTile == 'E' && hasKey) {
				map[heroY][heroX] = ' ';
				map[newHeroY][newHeroX] = 'H';
				victory = true;
			}
		}
	}

	public static void main(String[] args) {
		char[][] map = {
				{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
				{'X', 'H', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
				{'X', ' ', 'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
				{'X', 'D', 'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
				{'X', ' ', 'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
				{'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X'},
				{'X', ' ', 'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
				{'X', ' ', 'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
				{'X', 'K', 'X', 'X', ' ', ' ', ' ', ' ', ' ', 'X'},
				{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
		};

		Scanner scanner = new Scanner(System.in);
		Random rand = new Random();

		for(;;) {
			int possibleX = map[0].length-2;
			int possibleY = map.length-2;
			int doorPosition = rand.nextInt(possibleX*2 + possibleY*2);

			if(doorPosition < possibleX) {
				int targetX = 1+doorPosition;
				int verificationY = 1;

				if((map[verificationY][targetX-1] == 'X' || map[verificationY][targetX-1] == ' ') &&
						(map[verificationY][targetX] == ' ') &&
						(map[verificationY][targetX+1] == 'X' || map[verificationY][targetX+1] == ' '))
				{
					map[verificationY-1][targetX] = 'E';
					break;
				}
			}
			else if(doorPosition < possibleX + possibleY) {
				int targetY = 1+doorPosition-possibleX;
				int verificationX = map[targetY].length-2;

				if((map[targetY-1][verificationX] == 'X' || map[targetY-1][verificationX] == ' ') &&
						(map[targetY][verificationX] == ' ') &&
						(map[targetY+1][verificationX] == 'X' || map[targetY+1][verificationX] == ' '))
				{
					map[targetY][verificationX+1] = 'E';
					break;
				}
			}
			else if(doorPosition < 2*possibleX + possibleY) {
				int targetX = 1+doorPosition-possibleX-possibleY;
				int verificationY = map.length-2;

				if((map[verificationY][targetX-1] == 'X' || map[verificationY][targetX-1] == ' ') &&
						(map[verificationY][targetX] == ' ') &&
						(map[verificationY][targetX+1] == 'X' || map[verificationY][targetX+1] == ' '))
				{
					map[verificationY+1][targetX] = 'E';
					break;
				}
			}
			else {
				int targetY = 1+doorPosition-2*possibleX-possibleY;
				int verificationX = 1;

				if((map[targetY-1][verificationX] == 'X' || map[targetY-1][verificationX] == ' ') &&
						(map[targetY][verificationX] == ' ') &&
						(map[targetY+1][verificationX] == 'X' || map[targetY+1][verificationX] == ' '))
				{
					map[targetY][verificationX-1] = 'E';
					break;
				}
			}
		}

		gameLoop:
		for(;;) {
			printMap(map);
			System.out.print("Input: ");
			for(;;) {
				String input = scanner.nextLine();
				char direction = input.charAt(0);

				boolean hasInput = true;

				switch(direction) {
				case 'w': {
					walk(map, 0, -1);
				} break;

				case 'a': {
					walk(map, -1, 0);
				} break;

				case 's': {
					walk(map, 0, 1);
				} break;

				case 'd': {
					walk(map, 1, 0);
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

			if(checkProximityToDragon(map)) {
				System.out.println("You're dead.");
				break gameLoop;
			}

			if(victory) {
				System.out.println("Victory!");
				break gameLoop;
			}
		}

		scanner.close();
	}

}
