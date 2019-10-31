package dkeep.logic;

public abstract class Entity {
	public int x;
	public int y;
	public char symbol;
	
	public Entity(int x, int y, char symbol) {
		this.x = x;
		this.y = y;
		this.symbol = symbol;
	}
	
	public void draw(Map map) {
		if(checkIfInsideMap(map)) {
			map.map[y][x] = symbol;
		}
	}
	
	public boolean checkIfInsideMap(Map map) {
		return x >= 0 && x < map.width && y >= 0 && y < map.height;
	}
	
	public boolean isIn(int x, int y) {
		if(this.x == x && this.y == y) {
			return true;
		}
		
		return false;
	}
	
	public MoveType checkCollision(Entity entity, int x, int y) {
		MoveType type = null;
		
		if(isIn(x, y)) {
			type = new MoveType(MoveTypeEnum.Blocked);
		}
		
		return type;
	}
}
