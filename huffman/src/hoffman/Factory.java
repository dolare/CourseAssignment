/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package hoffman;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
/**
 * 工厂类
 * 编解码的场所
 * 含有一个后迭代器
 * @author afunx
 */
public class Factory <T extends SimpleBinaryTree>{
    //后迭代器,用于存储死亡的元素
    private int bacIte;
    //工厂大小
    private int size;
    //元素
    private T elements[];
    //工厂已经含有元素的个数
    private int nOfElements = 0;
    //反射类
    private Class c;
    /**
     * 容器方法，确保nOfInsrc>1
     * @param nOfInsrc  信源个数
     * @throws InstantiationException   实例初始化异常
     * @throws ClassNotFoundException   类发现异常
     * @throws IllegalAccessException   无法获得异常
     */
    public Factory(int nOfInsrc) throws InstantiationException,
            ClassNotFoundException, IllegalAccessException{
        T tClass = (T)new SimpleBinaryTree();
        size = calSize(nOfInsrc);
        bacIte = size-1;
        //反射机制
        c = tClass.getClass();
        //!!!T[] t = (T[])new Object[10];
        //不得不用SimpleBinaryTree，否则无法使用T extends SimpleBinaryTree
        elements= (T[])new SimpleBinaryTree[size];
        for(int i=0;i<size;i++){
            elements[i] = (T)c.newInstance();           
        }
    }
    /**
     * 辅助方法，根据信源数，计算数组大小，调用者应保证nOfInsrc>1
     * @param nOfInsrc  信源个数
     * @return 数组大小
     */
    private int calSize(int nOfInsrc){
        return(2*nOfInsrc-1);
    }
    /**
     * 增加新元素，不考虑数组空间不够
     * @param element 新增元素
     */
    public void addElement(T element){
        elements[nOfElements++]=element;
    }
    /**
     * 返回指定位置的元素
     * @param index 位置
     * @return index位置上的元素
     */
    public T getElement(int index){
        return(elements[index]);
    }
    /**
     * 返回当前工厂的大小
     * @return 当前工厂大小
     */
    public int getSize(){
        return size;
    }
    /**
     * 返回当前工厂元素已填充的个数
     * @return 当前工厂已填充个数
     */
    public int getOccupiedSize(){
        return nOfElements;
    }
    /**
     * 交换两元素的位置
     * @param index1    元素1的位置
     * @param index2    元素2的位置
     */
    public void swap(int index1,int index2) {
        T temp = elements[index1];
        elements[index1] = elements[index2];
        elements[index2] = temp;
    }
    /**
     * 某个元素死亡，即把它移到末尾,清楚之前的存储内容。
     * @param index 丢弃的元素位置
     */
    public void drop(int index){
        //移到最后
        T dieElement = elements[index];
        nOfElements--;
        elements[bacIte--]=dieElement;
        //清楚该元素之前存储的内容
        //由于移到末尾的是一引用，所以，不能删除该引用，而采用填入一个空白值的方式
        this.addElement((T)SimpleBinaryTree.factory());
        nOfElements--;
    }
    /**
     * toString()方法，调试用
     * @return Factory字符串
     */
    @Override
    public String toString(){
        String result = "";
        for(int i=0;i<size;i++){
            result += i+":";
            result += elements[i].toString();
        }
        return result;
    }
}
