/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package hoffman;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Vector;
/**
 * 字典类，用于存储码字元素及对应码字编码
 * @author afunx
 */
public class Dictionary {
    /**
     * 码字元素，如"a"、"b"、"c"、"d"
     */
    private Vector<Character> elements = new Vector();
    /**
     * 码字编码，如"0011"
     */
    private Vector<String> codes = new Vector();
    /**
     * 默认容器
     */
    public Dictionary(){
        
    }
    /**
     * 映射，若输入在码字编码中，则返回对应码字元素，否则返回^
     * @param input 输入码字编码
     * @return 对应码字元素
     */
    public char map(String input){
        int index = codes.indexOf(input);
        if(index==-1)
            return('^');
        return(elements.elementAt(index));
    }
   /**
     * 编码，根据字典，对输入字符进行编码
     * @param input 输入码字元素
     * @return 对应码字编码
     */
   public String code(char input){
       int index = elements.indexOf(input);
       return codes.elementAt(index);
   }
   /**
    * 码字元素数组访问器
    * @return 码字元素数组
    */
    public Vector<Character> getElements(){
        return elements;
    }
   /**
     * 码字编码数组访问器
     * @return 码字编码数组
     */
    public Vector<String> getCodes(){
        return codes;
    }
    /**
     * toString()方法，调试用
     * @return Dictionary字符串
     */
    @Override
    public String toString(){
        String result = "";
        for(int i=0;i<elements.size();i++){
            result +=elements.elementAt(i) +","+codes.elementAt(i)+"\r\n";
        }
        return(result);
    }
    /**
     * 输出到文件系统
     * @param toFile    输出文件
     * @throws FileNotFoundException    文件无法找到异常
     * @throws IOException IO异常
     */
    public void outputFile(File toFile) throws FileNotFoundException, IOException{
        //把结果输出到toFile文件
        FileOutputStream outputStream = new FileOutputStream(toFile);
        PrintStream out = new PrintStream(outputStream);
        //输出
        out.println(this);
        out.flush();
        //关闭输出流
        out.close();
        outputStream.close();
    }
    /**
     * 调试方法
     * @param args 调试参数
     */
    public static void main(String args[]){
        Dictionary dict = new Dictionary();
        String s = "null";
        dict.elements.add('a');
        dict.elements.add('b');
        dict.codes.add("11");
        dict.codes.add("01");
        System.out.println(dict.map("01"));
    }
}
