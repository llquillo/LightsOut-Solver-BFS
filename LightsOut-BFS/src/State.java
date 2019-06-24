public class State{
	public char[][] parentBoard = new char[5][5];
	public int moveX;
	public int moveY;
	public char[][] currentBoard = new char[5][5];
	public State previousState;

	public State(State previousState, char[][] parentBoard, int x, int y, char[][] currentBoard){
		this.previousState = previousState;
		this.parentBoard = parentBoard;
		this.moveX = x;
		this.moveY = y;
		this.currentBoard = currentBoard;
	}

	public int getMoveX(){
		return moveX;
	}

	public int getMoveY(){
		return moveY;
	}

	public State getPrevState(){
		return previousState;
	}
}