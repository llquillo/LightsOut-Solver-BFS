import java.io.*;
import javax.swing.*;
import java.util.*;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.LineBorder;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList; 
import java.util.Queue; 

public class Frame extends JFrame implements ActionListener{
  public static JButton[][] buttons = new JButton[5][5];
  public static char[][] tempBoard = new char[5][5];
  char n = 'n';
  Container container = this.getContentPane();
  JPanel stage = new JPanel();
  int flag = 0;


  public Frame(char[][] board){
    this.tempBoard = board;
    this.setPreferredSize(new Dimension(500, 500));
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


    stage.setLayout(new GridLayout(5, 5));
    this.initialize();
    container.add(stage);
    this.pack();
    this.setVisible(true);
  }

  public void setFrameBoard(char[][] board){
    this.tempBoard = board;
  }

  public void initialize(){
    char[][] solvedMap = new char[5][5];
    State finalState = this.solveGame();
    solvedMap = finalState.currentBoard;
    ArrayList<Integer> movesX = new ArrayList<Integer>();
    ArrayList<Integer> movesY = new ArrayList<Integer>();
    while(finalState.previousState!=null){
      movesX.add(finalState.moveX);
      movesY.add(finalState.moveY);

      finalState = finalState.previousState;
    }

    Collections.reverse(movesX);
    Collections.reverse(movesY);

    File answer = new File("puzzle.out");

    try{
      FileWriter fileWriter = new FileWriter(answer);
      BufferedWriter writer = new BufferedWriter(fileWriter);
      for(int i=0; i<movesX.size(); i++){
        writer.write(movesX.get(i) + ", " + movesY.get(i));
        writer.write("\n");
      }
      writer.close();
    }catch(Exception e){
          System.out.println("Error");
    }
  

    this.checkGameState();

    for(int x=0; x<5; x++){
			for(int y=0; y<5; y++){
        switch(tempBoard[x][y]){
          case 'n':
            buttons[x][y] = new JButton();
            buttons[x][y].setBackground(Color.YELLOW);
            buttons[x][y].setOpaque(true);
            buttons[x][y].setBorder(new LineBorder(Color.WHITE));
            buttons[x][y].addActionListener(this);
            stage.add(buttons[x][y]);
            break;
          case 'f':
            buttons[x][y] = new JButton();
            buttons[x][y].setBackground(Color.BLACK);
            buttons[x][y].setOpaque(true);
            buttons[x][y].setBorder(new LineBorder(Color.WHITE));
            buttons[x][y].addActionListener(this);
            stage.add(buttons[x][y]);
            break;
          default:
            System.out.println(tempBoard[x][y]);
        }
			}
		}
    return;
  }
  public void actionPerformed(ActionEvent e){
    this.checkGameState();
    if(flag==0){
      JLabel end = new JLabel("WINNER!", JLabel.CENTER);
      end.setFont(new Font("Serif", Font.PLAIN, 14));

      final JDialog dialog = new JDialog(this, "HELLO");
      dialog.setSize(300, 150);
      dialog.setLocationRelativeTo(this);
      dialog.add(end);
      dialog.setVisible(true);
      this.saveGame();
      return;
    }

    int x=0;
    int y=0;
    int a=0;
    int b=0;
    boolean done = true;
    if(e.getSource() instanceof JButton){
      for(x=0; x<5; x++){
        for(y=0; y<5; y++){
          if((JButton)e.getSource()==buttons[x][y]) {
            a = x;
            b = y;
            break;
          }
        }
      }
    }

    changeColor(a, b);
    if(checkUpBounds(a+1)==true){
      changeColor(a+1, b);
    }
    if(checkUpBounds(b+1)==true){
      changeColor(a, b+1);
    }
    if(checkDownBounds(a-1)==true){
      changeColor(a-1, b);
    }
    if(checkDownBounds(b-1)==true){
      changeColor(a, b-1);
    }
    this.saveGame();
    stage.revalidate();
    stage.repaint();

  }

  public State makeNewMap(State previousState, char[][] currentMap, int a, int b){
    char[][] newMap = new char[5][5];
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        newMap[i][j] = currentMap[i][j];
      }
    }

    int w = a;
    int z = b;

    changeColorNew(newMap, a, b);
    if(checkUpBounds(a+1)==true){
      changeColorNew(newMap, a+1, b);
    }
    if(checkUpBounds(b+1)==true){
      changeColorNew(newMap, a, b+1);
    }
    if(checkDownBounds(a-1)==true){
      changeColorNew(newMap, a-1, b);
    }
    if(checkDownBounds(b-1)==true){
      changeColorNew(newMap, a, b-1);
    }
    State aState = new State(previousState, currentMap, w, z, newMap);
    previousState = aState;
    return aState;
  }

  public void changeColorNew(char[][] newMap, int a, int b){
     switch(newMap[a][b]){
      case 'n':
        newMap[a][b] = 'f';
        return;
      case 'f':
        newMap[a][b] = 'n';
        return;
      default:
        System.out.println("error");
    }
  }

  public int plusOne(int num){
    return num++;
  }

  public int minusOne(int num){
    return num--;
  }

  public void changeColor(int a, int b){
    switch(tempBoard[a][b]){
      case 'n':
        tempBoard[a][b] = 'f';
        buttons[a][b].setBackground(Color.BLACK);
        buttons[a][b].setOpaque(true);
        buttons[a][b].setBorder(new LineBorder(Color.WHITE));
        return;
      case 'f':
        tempBoard[a][b] = 'n';
        buttons[a][b].setBackground(Color.YELLOW);
        buttons[a][b].setOpaque(true);
        buttons[a][b].setBorder(new LineBorder(Color.WHITE));
        return;
      default:
        System.out.println("error");
    }
  }

  public boolean checkUpBounds(int num){
    if(num>4){
      return false;
    }else{
      return true;
    }
  }

  public boolean checkDownBounds(int num){
    if(num<0){
      return false;
    }else{
      return true;
    }
  }

  public void checkGameState(){
    flag = 0;
    for(int x=0; x<5; x++){
      for(int y=0; y<5; y++){
        switch(tempBoard[x][y]){
          case 'n': flag+=1; break;
          default: break;
        }
      }
    }
  }

  public void saveGame(){
    File file = new File("./puzzle.in");
    
    try{
      FileWriter fileWriter = new FileWriter(file);
      BufferedWriter writer = new BufferedWriter(fileWriter);
      for(int x=0; x<5; x++){
        for(int y=0; y<5; y++){
          writer.write(tempBoard[x][y]);
          writer.write(" ");
        }
        writer.write("\n");
      }
      writer.close();
    }catch(Exception e){
          System.out.println("Error");
    }
  }

  public State solveGame(){
    Queue<State> frontier = new LinkedList<>();
    State initialState = new State(null, null, -1, -1, tempBoard);
    frontier.add(initialState);
    while(frontier!=null){
      State currentState = frontier.remove();
      char[][] board = currentState.currentBoard;
      int count = 0;
      for(int x=0; x<5; x++){
        for(int y=0; y<5; y++){
          switch(board[x][y]){
            case 'n': count+=1; break;
            default: break;
          }
        }
      }
      if(count==0){
        return currentState;
      }else{
        int n=0;
          for(int x=0; x<5; x++){
            for(int y=0; y<5; y++){
              if(board[x][y]=='n'){
                frontier.add(makeNewMap(currentState, board, x, y));
                n++;
              }
            }
          }
       } 
    }
    return null;
  }


}
