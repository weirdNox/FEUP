package dkeep.logic;

public class Key extends Entity {
	public Key(int x, int y) {
		super(x, y, 'K');
	}

	public MoveType checkCollision(Entity entity, int x, int y) {
		MoveType result = null;
		
		if(isIn(x, y)) {
			if(entity instanceof Hero) {
				result = new MoveType(MoveTypeEnum.Interaction);
				result.entity = this;
			}
			else {
				result = new MoveType(MoveTypeEnum.Allowed);
			}
		}
		
		return result;
	}
}
