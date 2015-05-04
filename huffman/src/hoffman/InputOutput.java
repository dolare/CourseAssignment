/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package hoffman;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Vector;
/**
 * 输入类，可以读入一个.txt文件，记录下码字，计算各自概率
 * 
 * @author afunx
 */
public class InputOutput {
    //总字符数
    private int totalCount =0;
    //码字元素
    private Vector<Character> codes;
    //码字频度
    private Vector<Integer> frequence;
    //码字概率
    private Vector<Double> probability;
    /**
     * 默认容器
     */
    public InputOutput(){
        codes = new Vector<Character>();
        frequence = new Vector<Integer>();
        probability = new Vector<Double>();
    }
    //get方法
    /**
     * 码字元素数组访问器
     * @return 码字元素数组
     */
    public Vector<Character> getCodes(){
        return codes;
    }
    /**
     * 码字频度数组访问器
     * @return 码字频度频度
     */
    public Vector<Integer> getFrequence(){
        return frequence;
    }
    /**
     * 码字概率数组访问器
     * @return 码字概率数组
     */
    public Vector<Double> getProbability(){
        return probability;
    }
    /**
     * 码字元素个数访问器
     * @return 码字元素个数
     */
    public int getCodesLength(){
        return codes.capacity();
    }
    /**
     * 读文件，记录各码字，并计算其出现概率
     * @param file  文件
     * @throws FileNotFoundException    文件未找到异常
     * @throws IOException              IO异常
     */
    public void read(File file) throws FileNotFoundException, IOException{
        //文件载入
        FileReader fr = new FileReader(file);
        BufferedReader buffer = new BufferedReader(fr);
        //从缓存读入一行数据
        String row = buffer.readLine();
        //直到读到null，表示文件结束，对文件进行解析
        //第二次读，代表有一个回车
        int nOfEnter = -1;
        while(row!=null){
            //解析一行字符串
            for(int i=0;i<row.length();i++){
                char word = row.charAt(i);
                //word在码字元素中的位置，返回-1表示不存在
                int index = codes.indexOf(word);
                //码字不存在，新加入码字
                if(index==-1){
                    codes.add(word);
                    //频率初始化为1
                    frequence.add(1);
                }
                //码字存在，对应码字频率加1
                else{
                    frequence.setElementAt(frequence.get(index)+1, index);
                }
                //总字符数加1
                totalCount++;
            }
            //回车数量增加
            nOfEnter++;
            //读入新的一行
            row = buffer.readLine();
        }
        //增加回车码字，及其次数
        if(nOfEnter>0){
            //总码字增加
            totalCount += nOfEnter;
            //增加码字
            codes.add('\n');
            //回车的频度
            frequence.add(nOfEnter);
        }
        //关闭输入流
        buffer.close();
        fr.close();
        //使各维度最小,并计算有效长度
        codes.trimToSize();
        frequence.trimToSize();
        probability.trimToSize();;
        //计算各码字概率
        int size = codes.capacity();
        for(int i=0;i<size;i++){
            probability.add(frequence.get(i)*1.0/totalCount);
        }
    }

    //根据字典实现编码
    /**
     * 根据字典实现编码
     * @param fromFile  原始文件
     * @param toFile    目标文件
     * @param dict      字典
     * @return          编码字符串
     * @throws FileNotFoundException    文件未找到异常
     * @throws IOException              IO异常
     */
    public String code(File fromFile,File toFile,Dictionary dict) throws FileNotFoundException, IOException{
        String result="";
        //文件载入
        FileReader fr = new FileReader(fromFile);
        BufferedReader buffer = new BufferedReader(fr);
        //从缓存读入一行数据
        String row = buffer.readLine();
        //直到读到null，表示文件结束，对文件进行解析
        while(row!=null){
            //解析一行字符串
            for(int i=0;i<row.length();i++){
                char word = row.charAt(i);
                //码字一定存在，编码,把a,b,c转换成诸如010100的东西
                result += dict.code(word);
            }
            //！！！加入空行
            result += dict.code('\n');
            //读入新的一行
            row = buffer.readLine();
        }
        //关闭输入流
        buffer.close();
        fr.close();
        //把结果输出到toFile文件
        FileOutputStream outputStream = new FileOutputStream(toFile);
        PrintStream out = new PrintStream(outputStream);
        //输出
        out.println(result);
        out.flush();
        //关闭输出流
        out.close();
        outputStream.close();
        return result;
    }
    /**
     * 根据字典解码
     * @param fromFile  原始文件
     * @param toFile    目标文件
     * @param dict      字典
     * @return          解码字符串
     * @throws FileNotFoundException    文件未找到异常
     * @throws IOException              IO异常
     */
    public String decode(File fromFile,File toFile,Dictionary dict) throws FileNotFoundException, IOException{
        //最终结果
        String result="";
        //文件载入
        FileReader fr = new FileReader(fromFile);
        BufferedReader buffer = new BufferedReader(fr);
        String input = buffer.readLine();
        System.out.println("input:"+input);
        //解析到第几位
        int index;
        //临时解析字符串
        String tempStr="";
        for(index=0;index<input.length();index++){
            tempStr += input.charAt(index);
            //解析成的字符串
            char decodeStr = dict.map(tempStr);
            //空格表示被解析的编码，无对应码字
            if(decodeStr!='^'){
                //****************************************
                //System.out.println("OK2");
                if(decodeStr=='\n'){
                    //System.out.println("OK");
                    result +='\r';
                }
                result += decodeStr;               
                tempStr = "";
            }
        }
        //把结果输出到toFile文件
        FileOutputStream outputStream = new FileOutputStream(toFile);
        PrintStream out = new PrintStream(outputStream);
        //输出
        out.println(result);
        out.flush();
        //关闭输出流
        out.close();
        outputStream.close();
        return result;
    }
    /**
     * toString()方法，调试用
     * @return InputOutput字符串
     */
    @Override
    public String toString(){
        return(this.getClass()+",codes:"+codes+",frequence:"+frequence
                +",probability:"+probability);
    }
    /**
     * 调试方法
     * @param args 调试参数
     */
    public static void main(String args[]) throws FileNotFoundException, 
            IOException, InstantiationException, ClassNotFoundException, IllegalAccessException{
        InputOutput input = new InputOutput();
        File file = new File("c:/infile.dat");
        File outFile = new File("c:/out.txt");
        File decodeFile = new File("c:/decode.txt");
        input.read(file);

        System.out.println(input);
        System.out.println(input.getCodesLength());

        int size = input.getCodesLength();
        //hoffman编解码器
        HoffMan<SimpleBinaryTree> hoffMan = new HoffMan(size);
        //把input的码字及概率添加到SimpleBinaryTree对象中
        for(int i=0;i<size;i++){
            String code = String.valueOf(input.getCodes().get(i));
            double probability = (input.getProbability().get(i));
            hoffMan.getFactory().addElement(new SimpleBinaryTree(null,null,null,probability,1,code,true));
        }
        hoffMan.coding();
        hoffMan.getDictionary().outputFile(new File("c:/dict.txt"));
        System.out.print("code:");
        System.out.println(input.code(file,outFile,hoffMan.getDictionary()));
        System.out.print("decod:");
        System.out.println(input.decode(outFile,decodeFile,hoffMan.getDictionary()));
    }
}
