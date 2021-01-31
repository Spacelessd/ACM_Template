/**
 * 
 * Pairing Heap   
 *  
 * Copyright (c) 2011 ljs (http://blog.csdn.net/ljsspace/)
 * Licensed under GPL (http://www.opensource.org/licenses/gpl-license.php) 
 * 
 * £Àauthor ljs
 * 2011-09-06
 *
 */
 #include<iostream>
 using namespace std;
                    class PairingHeap {
	//left-child£¬ right-sibling representation
	                    class Node{
		                    int key; 
		
		//left is the parent for first child; is the left sibling for other children
		                    Node *left;		
		
		                    Node *sibling;	
		
		//child points to the leftmost-child 
		                    Node *child;
				 
		                    Node(int key){
			this.key = key;
		}
		                    string toString(){
			return string.valueOf(this.key);
		}
	}
	
	                    Node *root;
	
	                    Node linkPair(Node first,Node second)
                        {
		if(second==null) return first;
		if(first==null) return second;
		
		if(first.key<second.key){
			//second is linked to first as a child
			
			//retain the sibling relation
			Node secondzSibling = second.sibling;
			first.sibling = secondzSibling;
			if(secondzSibling != null) secondzSibling.left = first;
			
			Node firstzChild = first.child;
			
			// second""s left and sibling pointers
			second.left = first;
			second.sibling = firstzChild;
			
			// first.child""s pointer
			if(firstzChild != null) firstzChild.left = second;
			
			// first""s child
			first.child = second;
			return first;
		}else{
			//first is linked to second as a child
			
			//retain the sibling relation
			Node firstzLeft = first.left;
			second.left = firstzLeft;
			if(firstzLeft != null){
				if(firstzLeft.child == first){
					//firstzLeft is first""s parent
					firstzLeft.child = second;
				}else{
					//firstzLeft is first""s left sibling					
					firstzLeft.sibling = second;
				}
			}			
			
			Node secondzChild = second.child;
			// first""s left and sibling pointers
			first.left = second;
			first.sibling = secondzChild;
			
			// second""s child pointer
			if(secondzChild != null) secondzChild.left = first;
			
			// second""s child
			second.child = first;
			return second;
		}
	}
	                    Node (Node node){
		if(root==null) 
			root = node;
		else
			root = linkPair(node£¬root);
		return node;
	}
	
	                    void decreaseKey(Node x£¬int k) throws Exception{
		if(x.key<k) throw new Exception("key is not decreased!");
		x.key = k;
		if(x!=root){
			//cut x subtree  its siblings
			Node xzLeft = x.left; 
			//if x is not root£¬ its left (i.e. xzLeft) can never be null
			if(xzLeft.child==x){//xzLeft is x""s parent
				xzLeft.child = x.sibling; 				
			}else{//xzLeft is x""s left sibling
				xzLeft.sibling = x.sibling;
			}
			if(x.sibling!=null){
				x.sibling.left = xzLeft;
			}
			
			//merge this tree with x subtree
			x.left = null;
			x.sibling = null;
			root = this.linkPair(x£¬ root);
		}
	}
	
	                    void merge(Node rhs){
		if(this.root==null) {
			this.root = rhs;
			return;
		}
		if(rhs==null) return;
		
		this.root = this.linkPair(this.root£¬ rhs);
	}
	                    Node findMin(){
		return this.root;
	}
	
	                    Node extractMin(){
		Node z = this.root;
		if(z!=null){
			if(z.child==null)
				root = null;
			else{
				Node firstSibling = z.child;
				firstSibling.left = null;				
				root = mergeSubHeaps(firstSibling);
			}
		}
		return z;
	}
	
	                    Node mergeSubHeaps(Node firstSibling){
		//the 1st pass: merge pairs  left side
		Node first = firstSibling;
		Node second = first.sibling;
				
		Node tail = first;
		if(second!=null){
			tail = this.linkPair(first£¬ second);
			first = tail.sibling;
			if(first!= null)
				second = first.sibling;
			else
				second = null;
		}
		while(first != null && second!=null){			
			tail = this.linkPair(first£¬ second);
			first = tail.sibling;
			if(first!= null)
				second = first.sibling;		
			else
				second = null;
		}
		
		//the 2nd pass: merge pairs  right side
		if(first!=null){
			tail = first;
		}
		
		Node prev = tail.left;
		while(prev!=null){
			tail = this.linkPair(prev£¬ tail);
			prev = tail.left;
		}
		return tail;
	}
	                    void print(){
		System.out.println("Pairing Heap:");
		this.print(0£¬ this.root);
	}
	
	                    void print(int level£¬ Node node){
		for (int i = 0; i < level; i++) {
            System.out.format(" ");
        }
		System.out.format("|");
        for (int i = 0; i < level; i++) {
        	System.out.format("-");
        }
        System.out.format("%d%n"£¬ node.key);
        Node child = node.child;
        while(child!=null){        	
        	print(level + 1£¬ child);
        	child = child.sibling;
        }       	
	}
	                                        void main(String[] args) throws Exception {
		PairingHeap pheap = new PairingHeap();
		Node node7=pheap.(new Node(7));
		pheap.(new Node(19));
		Node node2=pheap.(new Node(2));
		
		PairingHeap pheap2 = new PairingHeap();
		pheap2.(new Node(9));
		pheap2.(new Node(17));
		pheap2.(new Node(12));
		pheap2.(new Node(14));		
		pheap.merge(pheap2.root);
		
		pheap2 = new PairingHeap();
		pheap2.(new Node(15));
		pheap2.(new Node(18));
		pheap2.(new Node(16));
		pheap2.(new Node(5));
		Node node11=pheap2.(new Node(11));		
		pheap.merge(pheap2.root);
		
		pheap2 = new PairingHeap();
		pheap2.(new Node(4));
		pheap2.(new Node(8));		
		pheap.merge(pheap2.root);
		
		pheap2 = new PairingHeap();
		Node node3=pheap2.(new Node(3));
		pheap2.(new Node(13));
		pheap2.(new Node(10));
		pheap.merge(pheap2.root);
		
		pheap.(new Node(6));
		
		pheap.print();
		
		Node min = pheap.findMin();
		System.out.format("min: %d%n"£¬ min.key);
		
		pheap.decreaseKey(node11£¬ 0);
		pheap.decreaseKey(node7£¬ 4);
		pheap.decreaseKey(node2£¬ 1);
		pheap.decreaseKey(node3£¬ 2);
		
		min = pheap.extractMin();
		while(min!=null){
			System.out.format("%d "£¬min.key);
			min = pheap.extractMin();		
		}
	}

}
