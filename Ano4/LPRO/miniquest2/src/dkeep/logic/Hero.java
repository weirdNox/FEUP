package dkeep.logic;

public class Hero extends Entity {
	public boolean hasKey = false;
	
	public Hero(int x, int y) {
		super(x, y, 'H');
	}
	
	public void move(GameState state, Input input) {
		int deltaX = 0;
		int deltaY = 0;
		
		switch(input) {
		case up:    { deltaY = -1; } break;
		case down:  { deltaY =  1; } break;
		case left:  { deltaX = -1; } break;
		case right: { deltaX =  1; } break;
		}
		
		MoveType move = state.checkIfAvailableToMove(this, x+deltaX, y+deltaY);
		if(move == null || move.type == MoveTypeEnum.Allowed) {
			this.x += deltaX;
			this.y += deltaY;
		}
		else if(move.type == MoveTypeEnum.Interaction) {
			this.x += deltaX;
			this.y += deltaY;

			if(move.entity instanceof Key) {
				hasKey = true;
				state.removeEntity(move.entity);
			}
			else if(move.entity instanceof Door) {
				state.end(true);
			}
			else if(move.entity instanceof Dragon) {
				state.end(false);
			}
		}
	}
}
