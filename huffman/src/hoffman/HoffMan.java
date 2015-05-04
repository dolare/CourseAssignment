
package hoffman;

import java.lang.reflect.InvocationTargetException;

public class HoffMan<T extends SimpleBinaryTree> {
      //鏄惁瀹屾垚缂栫爜
      private boolean codingFinished = false;
      //瀛楀吀
      private Dictionary dict = new Dictionary();
      //缂栫爜宸ュ巶
      private Factory<SimpleBinaryTree> factory;// = new Factory(5);
   
      public HoffMan(int nOfInforsrc) throws InstantiationException, ClassNotFoundException,
              IllegalAccessException{
          factory = new Factory(nOfInforsrc);
      }
     
      public boolean isFinished(){
          return codingFinished;
      }
    
      public Factory<SimpleBinaryTree> getFactory(){
          return factory;
      }
  
      public Dictionary getDictionary(){
          return dict;
      }
   
      public void sort(){
          
          int valid = factory.getOccupiedSize();
    
          for(int i=valid;i>0;i--){
              for(int j=0;j<i-1;j++){
                  if(factory.getElement(j).getPro()<factory.getElement(j+1).getPro()){
                      factory.swap(j,j+1);
                  }
                
                  if(factory.getElement(j).getPro()==factory.getElement(j+1).getPro()){
                      if(factory.getElement(j).getInforsrc()<factory.getElement(j+1).getInforsrc())
                          factory.swap(j, j+1);
                  }
              }
          }
      }

    public void merge() throws InstantiationException, IllegalAccessException {
        T mixture = (T)SimpleBinaryTree.factory();
        
        int index1 = factory.getOccupiedSize()-1;
        int index2 = factory.getOccupiedSize()-2;
      
        if(index2<0){
            codingFinished = true;
            return;
        }
        
        mixture.setLeftChild(factory.getElement(index2));
        mixture.setRightChild(factory.getElement(index1));
        factory.getElement(index2).setParent(mixture);
        factory.getElement(index1).setParent(mixture);
       
        mixture.setPro(factory.getElement(index1).getPro()
                +factory.getElement(index2).getPro());
        mixture.setInforsrc(factory.getElement(index1).getInforsrc()
                +factory.getElement(index2).getInforsrc());
        mixture.setCodeWord(factory.getElement(index1).getCodeWord()
                +factory.getElement(index2).getCodeWord());
        mixture.setAlive(true);

        factory.drop(index1);
        factory.drop(index2);
        factory.addElement(mixture);
    }

    public void coding() throws InstantiationException, IllegalAccessException{
     
        while(!codingFinished){
            this.sort();
            this.merge();
        }
        for(int i=0;i<factory.getSize();i++){
            T element = (T)factory.getElement(i);
            T parent = (T)element.getParent();
            String result ="";
            
            if(element.getInforsrc()==1&&element.getAlive()){
                System.out.print(factory.getElement(i).getCodeWord()+":");
      
                dict.getElements().addElement(factory.getElement(i).getCodeWord().charAt(0));
                while(parent!=null){
                    if(element.isLeftChild(parent))
                        result+="0";
                    else
                        result+="1";
                    element = parent;
                    parent = (T)element.getParent();
                }
        
                String finalResult="";
                for(int k=0;k<result.length();k++)
                    finalResult+=result.charAt(result.length()-k-1);
        
                dict.getCodes().addElement(finalResult);
                System.out.println(finalResult);
            }            
        }
    }

    public void decoding(String input){
     
        int index;
     
        String tempStr="";
       
        String result="";
        for(index=0;index<input.length();index++){
            tempStr += input.charAt(index);
          
            char decodeStr = dict.map(tempStr);
      
            if(decodeStr!='^'){
                result += decodeStr;
                tempStr = "";
            }
        }
        System.out.println(result);
    }
  
    public static void main(String[] args) throws InstantiationException,IllegalAccessException, 
    ClassNotFoundException, NoSuchMethodException, IllegalArgumentException, InvocationTargetException{
        Factory<SimpleBinaryTree> factory = new Factory(5);//,new SimpleBinaryTree());
        SimpleBinaryTree sBT0= new SimpleBinaryTree(null,null,null,0.4,1,"a",true);
        SimpleBinaryTree sBT1= new SimpleBinaryTree(null,null,null,0.2,1,"b",true);
        SimpleBinaryTree sBT2= new SimpleBinaryTree(null,null,null,0.2,1,"c",true);
        SimpleBinaryTree sBT3= new SimpleBinaryTree(null,null,null,0.1,1,"d",true);
        SimpleBinaryTree sBT4= new SimpleBinaryTree(null,null,null,0.1,1,"e",true);
        HoffMan<SimpleBinaryTree> hoffMan = new HoffMan(5);
        hoffMan.factory.addElement(sBT0);
        hoffMan.factory.addElement(sBT1);
        hoffMan.factory.addElement(sBT2);
        hoffMan.factory.addElement(sBT3);
        hoffMan.factory.addElement(sBT4);
        hoffMan.coding();
        hoffMan.decoding("11100101100");
    }
}
