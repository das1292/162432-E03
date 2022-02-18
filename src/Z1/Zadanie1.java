package Z1;

import java.time.LocalDate;
import java.util.LinkedList;

public class Zadanie1 {
    public static void main(String[] args){
    LinkedList<Integer> int1=new LinkedList<>();
    int1.add(1);
    int1.add(2);
    int1.add(3);
    int1.add(4);
    int1.add(5);
    System.out.println(redukuj(int1,2));
    LinkedList<LocalDate> LD1=new LinkedList<>();
    LD1.add(LocalDate.of(2000,11,11));
    LD1.add(LocalDate.of(2020,10,10));
    LD1.add(LocalDate.of(2010,1,1));
    LD1.add(LocalDate.of(2012,2,21));
    System.out.println(redukuj(LD1,3));
    }
    public static <E extends LinkedList<?>>LinkedList redukuj(E list, int n){
        for(int i=n-1;i<list.size();i=i+n-1){
            list.remove(i);
        }
        return list;
    }
}
