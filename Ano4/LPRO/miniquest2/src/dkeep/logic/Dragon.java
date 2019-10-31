package dkeep.logic;

import java.util.ArrayList; 
import java.util.Random;

public class Dragon extends Entity {
	public Dragon(int x, int y) {
		super(x, y, 'D');
	}

	public MoveType checkCollision(Entity entity, int x, int y) {
		MoveType result = null;
		
		if(entity instanceof Hero) {
			if((x >= this.x - 1) && (x <= this.x + 1) &&
					(y >= this.y - 1) && (y <= this.y + 1))
			{
				result = new MoveType(MoveTypeEnum.Interaction);
				result.entity = this;
			}
		}
		else if(isIn(x, y)) {
			result = new MoveType(MoveTypeEnum.Blocked);
		}
		
		return result;
	}
	
	public void move(GameState state) {
		int possiblePos[][] = {
				{x+1, y},
				{x+1, y+1},
				{x,   y+1},
				{x-1, y+1},
				{x-1, y},
				{x-1, y-1},
				{x,   y-1},
				{x+1, y-1},
		};
		
		ArrayList<int[]> possible = new ArrayList<int[]>();
		
		for(int[] test : possiblePos) {
			MoveType type = state.checkIfAvailableToMove(this, test[0], test[1]);
			if(type == null || type.type == MoveTypeEnum.Allowed) {
				possible.add(test);
			}
		}
		
		if(possible.size() > 0) {
			Random rand = new Random(); 
			int possibleIdx = rand.nextInt(possible.size());

			x = possible.get(possibleIdx)[0];
			y = possible.get(possibleIdx)[1];
		}
	}
}

