package dkeep.logic;

import java.util.List; 
import java.util.ArrayList; 

public class GameState {
	public Map map;
	List<Entity> entities = new ArrayList<Entity>();
	List<Entity> blockers = new ArrayList<Entity>();
	List<Entity> others = new ArrayList<Entity>();
	public Hero hero;
	
	public boolean done;
	
	public GameState() {
		map = new Map(10, 10);

		addEntity(new Hero(5, 5));

		addEntity(new Wall(0, 0, 9, 1));
		addEntity(new Wall(1, 9, 9, 1));
		addEntity(new Wall(9, 0, 1, 4));
		addEntity(new Door(9, 4));
		addEntity(new Wall(9, 5, 1, 4));
		addEntity(new Wall(0, 1, 1, 9));

		addEntity(new Key(1, 1));
		addEntity(new Dragon(5, 1));
		addEntity(new Dragon(6, 1));
		addEntity(new Dragon(7, 1));

		addEntity(new Wall(4, 2, 3, 1));
		addEntity(new Wall(1, 4, 3, 1));
		addEntity(new Wall(4, 2, 3, 1));
	}
	
	public void draw() {
		map.drawMap(entities);
	}
	
	public void addEntity(Entity entity) {
		entities.add(entity);
		
		if(entity instanceof Hero) {
			hero = (Hero)entity;
		}
		
		if(entity instanceof Wall) {
			blockers.add((Wall)entity);
		}
		else {
			others.add(entity);
		}
	}
	
	public boolean tick(Input input) {
		for(Entity entity : others) {
			if(entity instanceof Dragon) {
				Dragon dragon = (Dragon)entity;
				dragon.move(this);
			}
		}
		hero.move(this, input);
		draw();
		
		return done;
	}
	
	public MoveType checkIfAvailableToMove(Entity entity, int x, int y) {
		MoveType result = null;
		
		if(x >= 0 && x < map.width && y >= 0 && y < map.height) {
			if(result == null) {
				for(Entity blocker : blockers) {
					result = blocker.checkCollision(entity, x, y);
					if(result != null) {
						break;
					}
				}
			}

			if(result == null) {
				for(Entity other : others) {
					result = other.checkCollision(entity, x, y);
					if(result != null) {
						break;
					}
				}
			}
		}
		else {
			result = new MoveType(MoveTypeEnum.Blocked);
		}
		
		return result;
	}
	
	public void removeEntity(Entity entity) {
		entities.remove(entity);
		blockers.remove(entity);
		others.remove(entity);
	}
	
	public void end(boolean victory) {
		if(victory) {
			System.out.println("Victory!");
		}
		else {
			System.out.println("You died!");
		}
		
		done = true;
	}
}
