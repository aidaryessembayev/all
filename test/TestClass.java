
package csci152.test;
import java.util.Set;
import java.util.HashSet;



public class TestClass {
    public static void main(String[] args) throws Exception{
        Set<Integer> hard = new HashSet<Integer>();
        
        hard.add(5);
        hard.add(12);
        hard.add(3);
        hard.add(6);
        hard.add(14);
        hard.add(2);
        hard.add(-6);
        hard.add(8);
        hard.add(0);
        
        System.out.println(hard);
        System.out.println(hard.size());
        
        hard.add(14);
        hard.add(-6);
        hard.add(5);
        
        System.out.println(hard);
        System.out.println(hard.size());
        
        System.out.println(hard.contains(12));
        System.out.println(hard.contains(7));
        System.out.println(hard.contains(2));
        System.out.println(hard.contains(-8));
        System.out.println(hard.contains(5));
        
        System.out.println(hard);
        System.out.println(hard.size());
        
        hard.clear();
        
        System.out.println(hard);
        System.out.println(hard.size());
        
        hard.add(55);
        hard.add(24);
        hard.add(78);
        hard.add(51);
        
        System.out.println(hard);
        System.out.println(hard.size());
    }
}
