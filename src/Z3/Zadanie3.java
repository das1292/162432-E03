package Z3;

import java.io.File;
import java.util.Arrays;
import java.util.Objects;

public class Zadanie3 {
    public static void main(String[] args){
        File file=new File("src/");
        String[] str=file.list();
        assert str!=null;
        Arrays.stream(str).map(i->{if(!i.contains("."))return i;return null;}).filter(Objects::nonNull).forEach(System.out::println);
    }
}
