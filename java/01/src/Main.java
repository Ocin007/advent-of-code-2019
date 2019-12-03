import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        Collection<Integer> input = Main.getInput();
        if(input == null) {
            System.exit(-1);
        }

        int result = input.stream()
                .map(mass -> (mass / 3) - 2)
                .reduce(0, (mass1, mass2) -> mass1 + mass2);

        System.out.println("Result is: "+result);
    }

    private static ArrayList<Integer> getInput() {
        Path path = Paths.get(System.getProperty("user.dir")+"\\..\\input\\01\\input.txt");
        try {
            List<String> allLines = Files.readAllLines(path, StandardCharsets.UTF_8);
            ArrayList<Integer> input = new ArrayList<>();
            allLines.forEach(string -> input.add(Integer.parseInt(string)));
            return input;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
