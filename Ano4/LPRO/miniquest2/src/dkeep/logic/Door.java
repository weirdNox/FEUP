package dkeep.logic;

public class Door extends Entity {

	public Door(int x, int y) {
		super(x, y, 'E');
	}

	public MoveType checkCollision(Entity entity, int x, int y) {
		MoveType result = null;
				
		if(isIn(x, y)) {
			if(entity instanceof Hero) {
				Hero hero = (Hero)entity;
				if(hero.hasKey) {
					result = new MoveType(MoveTypeEnum.Interaction);
					result.entity = this;
				}
				else {
					result = new MoveType(MoveTypeEnum.Blocked);
				}
			}
			else {
				result = new MoveType(MoveTypeEnum.Blocked);
			}
		}
		
		return result;
	}

}
