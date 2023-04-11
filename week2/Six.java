import java.io.File;
import java.io.FileNotFoundException; 
import java.util.Scanner;

class Six {
  Array<String> read_file(String file_path){
    try {
      File f = new File(file_path);
      Scanner reader = new Scanner(f);
      while(reader.hasNextLine()){
        String data = myReader.nextLine();
        System.out.println(data);
      }
      myReader.close();
    } catch (FileNotFoundException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
  }
  public static void main(String[] args){
  }
}
