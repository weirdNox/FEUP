package dkeep.logic;

public class Wall extends Entity {
	int width;
	int height;
	
	public Wall(int x, int y, int width, int height) {
		super(x, y, 'X');
		this.height = height;
		this.width = width;
	}

	public void draw(Map map) {
		if(checkIfInsideMap(map)) {
			for(int y = this.y; y < this.y + height; ++y) {
				for(int x = this.x; x < this.x + width; ++x) {
					map.map[y][x] = symbol;
				}
			}
		}
	}
	
	public boolean isIn(int x, int y) {
		if(this.x <= x && this.x + width > x && this.y <= y && this.y + height > y) {
			return true;
		}
		
		return false;
	}
}
