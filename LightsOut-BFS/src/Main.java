import java.io.*;
import javax.swing.*;
import java.util.*;
public class Main{
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
		char[][] tempBoard = new char[5][5];
		char space = ' ';
    String line;
    char[] chars = new char[5];

		try{
			File file = new File("puzzle.in");
			Scanner scanner = new Scanner(file);

			for(int j=0; scanner.hasNextLine() && j<10; j++){
        line = scanner.nextLine();
        String lineTrimmed = line.replaceAll("\\s", "");
        chars = lineTrimmed.toCharArray();
        for(int i=0; i<5 && i<chars.length; i++){
          tempBoard[j][i] = chars[i];

        }

			}
		}catch(Exception e){
          System.out.println("File not found.");
    }

    Frame frame = new Frame(tempBoard);
  }
}
