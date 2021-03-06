import java.util.*;

class node{
	public int Data;
	public node Next = null;
	public node Prev = null;
	
	public node()
	{
	}
	
	public node(int Data)
	{
		this.Data = Data;
	}
}

class DoublyList {
	private int Count;							// 리스트 길이
	private node Head;
	
	public DoublyList()
	{
		Count = 0;
		Head = null;
	}
	
	public DoublyList(DoublyList DL)			// 리스트 복사
	{
		Count = DL.Count;
		if(DL.Head == null)
			Head = null;
		else
		{
			Head = new node();
			Head.Data = DL.Head.Data;
			node temp1 = Head;
			for(node temp2 = DL.Head.Next;
					temp2 != null; temp2 = temp2.Next)
			{
				temp1.Next = new node(temp2.Data);
				temp1.Next.Prev = temp1;
				temp1 = temp1.Next;
			}
			temp1.Next = null;
		}
	}
	
	public void Insert(int Position, int Item)	// 값 삽입
	{
		if((Position > (Count + 1)) || (Position < 1))
				System.out.println("Position out of Range");
		else
		{
			node temp = new node(Item);
			if(Position == 1)
			{
				temp.Next = Head;
				if(Head != null)
					Head.Prev = temp;
				Head = temp;
			}
			else
			{
				node headTemp = Head;
				for(int i = 1; i < (Position - 1); i++)
					headTemp = headTemp.Next;
				if(headTemp.Next != null)
				{
					temp.Next = headTemp.Next;
					headTemp.Next.Prev = temp;
				}
				else
					temp.Next = null;
				headTemp.Next = temp;
				temp.Prev = headTemp;
			}
			Count++;
		}
	}
	
	public void Delete(int Position)			// 값 삭제
	{
		if(IsEmpty())
			System.out.println("Deletion on Empty List");
		else if((Position > Count) || (Position < 1))
			System.out.println("Position out of Range");
		else
		{
			if(Position == 1)
			{
				Head = Head.Next;
			}
			else
			{
				node headTemp = Head;
				for(int i = 1; i < (Position-1); i++)
					headTemp = headTemp.Next;
				if(headTemp.Next.Next != null)
				{
					headTemp.Next = headTemp.Next.Next;
					headTemp.Next.Next.Prev = headTemp;
				}
				else
					headTemp.Next = null;
			}
			Count--;
		}
		
	}
	
	public int Retrieve(int Position)			// 값 검색
	{
		if(Position == 1)
			return Head.Data;
		else
		{
			node temp = Head;
			for(int i = 1; i < Position; i++)
				temp = temp.Next;
			return temp.Data;
		}
	}
	
	public boolean IsEmpty()					// 리스트가 비었는지 확인
	{
		return (Count == 0);
	}
	
	public int Length()							// 리스트 길이 반환
	{
		return Count;
	}
}

public class DoublylinkedList {

	static void PrintList(DoublyList DL)		// 리스트를 출력하는 함수
	{
		for(int i = 1; i <= DL.Length(); i++)
		{
			if((i > DL.Length()) || (i < 1))
				System.out.println("Position out of Range");
			else
				System.out.print(DL.Retrieve(i) + " ");
		}
		System.out.println();
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scanner =  new Scanner(System.in);
		DoublyList DL = new DoublyList();
		int input, position;
		
		while(true)
		{
			System.out.print("Insert : 1, Delete : 2, Retrieve : 3, Copy List : 4, Is Empty? : 5, Length : 6, Exit : 0 >> ");
			input = scanner.nextInt();
			if(input == 0)
				break;
			switch(input)
			{
			case 1:
				System.out.print("Insert Position and Number >> ");
				position = scanner.nextInt();
				input = scanner.nextInt();
				DL.Insert(position, input);
				System.out.print("List item : ");
				PrintList(DL);
				break;
			case 2:
				System.out.print("Delete Position >> ");
				position = scanner.nextInt();
				DL.Delete(position);
				System.out.print("List item : ");
				PrintList(DL);
				break;
			case 3:
				int item;
				System.out.print("Retrieve Position >> ");
				position = scanner.nextInt();
				if(position > DL.Length() || position < 1)
					System.out.println("Position out of Range");
				else {
					item = DL.Retrieve(position);
					System.out.println("item : " + item);
					System.out.print("List item : ");
					PrintList(DL);
				}
				break;
			case 4:
				DoublyList DL2 = new DoublyList(DL);
				System.out.print("List1 item : ");
				PrintList(DL);
				System.out.print("New List item : ");
				PrintList(DL2);
				break;
			case 5:
				System.out.println((DL.IsEmpty()) ? "Empty" : "Not Empty");
				break;
			case 6:
				System.out.println(DL.Length());
				break;
			}
		}
		scanner.close();
	}

}
