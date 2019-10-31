package dkeep.logic;

import java.util.List; 

public class Map {
	int width;
	int height;
	char[][] map;
	
	public Map(int width, int height) {
		this.width = width;
		this.height = height;
		this.map = new char[height][width];
	}
	
	public void drawMap(List<Entity> entities) {
		for(int y = 0; y < height; ++y) {
			for(int x = 0; x < width; ++x) {
				map[y][x] = ' ';
			}
		}
		
		for(Entity entity : entities) {
			entity.draw(this);
		}
		
		for(int y = 0; y < height; ++y) {
			for(int x = 0; x < width; ++x) {
				if(map[y][x] == '\u0000') {
					System.out.print(' ');
				}
				else {
					System.out.print(map[y][x]);
				}
			}
			
			System.out.print('\n');
		}
	}
}
