/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package hoffman;

/**
 * 定义一个简单二叉树，不包含删除节点的方法。
 * @author afunx
 */
public class SimpleBinaryTree {
    //父节点
    private SimpleBinaryTree parent = null;
    //左子节点
    private SimpleBinaryTree leftChild = null;
    //右子节点
    private SimpleBinaryTree rightChild = null;
    //出现概率
    private double pro = 0;
    //该节点所含信源个数
    private int inforsrc = 0;
    //***该节点是否存活
    //***若两节点合并为一个新节点后，此二节点死亡，新节点存活
    private boolean alive = false;
    //***排序时，该节点所在顺序
    //***private int order = -1;
    //码字
    private String codeWord="";
    /**
     * 默认容器
     */
    public SimpleBinaryTree(){

    }
    /**
     * 容器方法
     * @param parent        父节点
     * @param leftChild     左子节点
     * @param rightChild    右子节点
     * @param pro           出现概率
     * @param inforsrc      信源个数
     * @param codeWord      码字元素字符串
     * @param alive         生存
     */
    public SimpleBinaryTree(SimpleBinaryTree parent,SimpleBinaryTree leftChild,
            SimpleBinaryTree rightChild,double pro,int inforsrc,String codeWord,boolean alive){
        this.parent = parent;
        this.leftChild = leftChild;
        this.rightChild = rightChild;
        this.pro = pro;
        this.inforsrc = inforsrc;
        //***this.order = order;
        this.codeWord = codeWord;
        //***在默认状态下，为false,使得工厂中生产的元素alive=false
        //***在此为true，使得之后，真正产生的alive=true
        this.alive = alive;
    }
    /**
     * 工厂方法
     * @return  SimpleBinaryTree实例 
     */
    public static SimpleBinaryTree factory(){
        return(new SimpleBinaryTree());
    }
    //set方法
    /**
     * 父节点设置器
     * @param parent    父节点 
     */
    public void setParent(SimpleBinaryTree parent){
        this.parent = parent;
    }
    /**
     * 左子节点设置器
     * @param leftChild 左子节点 
     */
    public void setLeftChild(SimpleBinaryTree leftChild){
        this.leftChild = leftChild;
    }
    /**
     * 右子节点设置器
     * @param rightChild    右子节点 
     */
    public void setRightChild(SimpleBinaryTree rightChild){
        this.rightChild = rightChild;
    }
    /**
     * 概率设置器
     * @param pro   出现概率 
     */
    public void setPro(double pro){
        this.pro = pro;
    }
    /**
     * 信源数设置器
     * @param inforsrc  信源个数 
     */
    public void setInforsrc(int inforsrc){
        this.inforsrc = inforsrc;
    }
    /**
     * 码字元素字符串设置器
     * @param codeWord 码字元素字符串
     */
    public void setCodeWord(String codeWord){
        this.codeWord = codeWord;
    }
    /**
     * 生存状态设置器
     * @param alive 生存 
     */
    public void setAlive(boolean alive){
        this.alive = alive;
    }
    //get方法
    /**
     * 概率访问器
     * @return 出现概率
     */
    public double getPro(){
        return pro;
    }
    /**
     * 信源数访问器
     * @return 信源个数
     */
    public int getInforsrc(){
        return inforsrc;
    }
    /**
     * 父节点访问器
     * @return 父节点
     */
    public SimpleBinaryTree getParent(){
        return parent;
    }
    /**
     * 码字元素字符串访问器
     * @return 码字元素字符串
     */
    public String getCodeWord(){
        return codeWord;
    }
    /**
     * 生存状态访问器
     * @return 生存状态
     */
    public boolean getAlive(){
        return alive;
    }

    //判断是否为父节点的左右子节点
    /**
     * 左子节点判断器
     * @param parent    父节点
     * @return 是否是parent的左子节点
     */
    public boolean isLeftChild(SimpleBinaryTree parent){
        return(this==parent.leftChild);
    }
    /**
     * 右子节点判断器
     * @param parent    父节点
     * @return 是否是parent的右子节点
     */
    public boolean isRightChild(SimpleBinaryTree parent){
        return(this==parent.rightChild);
    }
    /**
     * 根节点判断器
     * @return 是否是根节点
     */
    public boolean isRoot(){
        return(this.parent==null);
    }
     /**
     * toString()方法，调试用
     * @return Dictionary字符串
     */
    @Override
    public String toString(){
        String parentStr,leftChildStr,rightChildStr;
        if(this.parent==null)
            parentStr="null";
        else
            parentStr=this.parent.getCodeWord();

        if(this.leftChild==null)
            leftChildStr="null";
        else
            leftChildStr=this.leftChild.getCodeWord();
        if(this.rightChild==null)
            rightChildStr="null";
        else
            rightChildStr=this.rightChild.getCodeWord();
        return("[parentWord:"+parentStr+",leftChildWord:"+leftChildStr+
                ",rightChildWord:"+rightChildStr+"\n"+
                "pro:"+pro+",inforsrc:"+inforsrc+",codeWord:"+codeWord+
                "alive:"+alive+"]\n");
    }
}

