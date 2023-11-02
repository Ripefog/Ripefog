#include "main.h"

class imp_res : public Restaurant
{
	class DS_KH_Time;
private:
	customer * KH_Queue;
	customer * KH_X; 

	int size_KH_In_Desk; 
	int size_KH_Queue; 

	DS_KH_Time * KH_Time_Head; 
	DS_KH_Time * KH_Time_Tail; 

private:

	customer* get_KH_At(customer* x, int index)
	{
		for(int i = 0; i < index; i++) x = x->next;
		
		return x;
	}

	customer* reverse_HEAD(customer* head, int energy)
	{
		for(int i = 0; i < size_KH_In_Desk ;i++)
		{
			if(head->energy * energy > 0) break;
			head = head->prev;
		}
		return head;
	}
	customer* reverse_TAIL(customer* tail, int energy)
	{
		for(int i = 0; i < size_KH_In_Desk; i++)
		{
			if(tail->energy * energy > 0) break;
			tail = tail->next;
		}
		return tail;
	}
	DS_KH_Time* find_KH_Xoa()
	{
		DS_KH_Time* KH_Xoa = KH_Time_Head;
		
		
		for(int i = 0; i < size_KH_Queue + size_KH_In_Desk; i++)
		{
			
			if(KH_Xoa->check_in_disk==true){
				break;
			}
			KH_Xoa = KH_Xoa->next;
		}
			
		
		
		if(size_KH_Queue + size_KH_In_Desk == 1)
		{
			
			KH_Time_Head = KH_Time_Tail = nullptr;
			
			
		}
		
		else if(KH_Xoa == KH_Time_Head)
		{
			
			KH_Xoa->next->prev = nullptr;
			
			KH_Time_Head=KH_Time_Head->next;
		
			 
		}
	
		else if(KH_Xoa == KH_Time_Tail)
		{
			
		
			KH_Time_Tail->prev->next=KH_Time_Tail->next;
			KH_Time_Tail=KH_Time_Tail->prev;
		}
		
		else
		{
			
			KH_Xoa->prev->next=KH_Xoa->next;
			KH_Xoa->next->prev=KH_Xoa->prev;
			
		}
		
		return KH_Xoa;	
		
	}
	
	
	void delete_KH_Time(DS_KH_Time* KH_Xoa)
	{
		
		if(KH_Xoa->check_in_disk == true)
		{
			
			if(size_KH_In_Desk == 1)
			{
				size_KH_In_Desk = 0;
				KH_X = nullptr;
			}
		
			else
			{
				customer* customerDelete = KH_Xoa->data;
				customer* next_cus = customerDelete->next;			
				customer* prev_cus = customerDelete->prev;
				next_cus->prev=prev_cus;
				prev_cus->next=next_cus;

				if(customerDelete->energy > 0)
				{
					KH_X=next_cus;
					
				}
				else
				{
					KH_X=prev_cus;
				}
				size_KH_In_Desk--; 
				
			}
		}
		
		else
		{
			
			if(size_KH_Queue == 1)
			{
				size_KH_Queue = 0;
				KH_Queue = nullptr;
			}
		
			else
			{
				customer* customerDelete = KH_Xoa->data;

			
				 	customerDelete->next->prev=customerDelete->prev;
					customerDelete->prev->next=customerDelete->next;

				
				if(customerDelete == KH_Queue) KH_Queue = KH_Queue->next;
				size_KH_Queue--; 
			}
		}
	
		delete KH_Xoa; 
		
	}
	
	void add_KH_to_DS_Time(customer*temp,bool check){
		DS_KH_Time* KH_Time_new = new DS_KH_Time (temp, check);
		KH_Time_Tail->next = KH_Time_new;
		KH_Time_new->prev = KH_Time_Tail;
		KH_Time_Tail = KH_Time_Tail->next;
	}
	void add_thuanKDH(customer*a){
		a->next = KH_X->next;
		a->prev = KH_X;
		KH_X->next->prev = a;
		KH_X->next = a;
	}
	void add_nghichKDH(customer*b){
		 b->prev = KH_X->prev;
		 b->next = KH_X;
		 KH_X->prev->next = b;
		 KH_X->prev = b;
	}
	bool Check_KH(customer*a,customer*b){
		DS_KH_Time*temp=KH_Time_Head;
		while(temp!=NULL){
			if(temp->data == a ) return false;
			else if(temp->data == b) return true;
			temp=temp->next;
		}
		return true;
	}

	void insert_KH_FromQueueToDisk()
	{
		
		while(size_KH_Queue != 0 && size_KH_In_Desk != MAXSIZE)
		{
			
			customer* KH_new = KH_Queue;

			
			DS_KH_Time* temp = KH_Time_Head; 
			for(int i = 0; i < size_KH_Queue + size_KH_In_Desk; i++)
			{
				
				if(temp->data==KH_new){
					temp->check_in_disk = true;
               		 break;
				}
				temp = temp->next;
			}
			
			if(size_KH_Queue == 1) KH_Queue = nullptr;
			else
			{
				
				
				KH_Queue->next->prev = KH_Queue->prev;
				KH_Queue->prev->next = KH_Queue->next;
				KH_Queue = KH_Queue->next;
            	
           		
			}
			size_KH_Queue --;

			
			if(size_KH_In_Desk == 0)
			{
				KH_X = KH_new;
				KH_new->next = KH_new->prev = KH_new;
			}
			else 
			{
			
				if(size_KH_In_Desk >= MAXSIZE / 2)
				{
					
					customer* temp; 
					temp = KH_X;
					
					customer* customerMax_diff = temp;
					
					int max_diff = 0;
					if(temp!=NULL){
						do{
						int res = abs(KH_new->energy - temp->energy);
						if (res > max_diff) {
							
							max_diff = res;
							customerMax_diff = temp;
							
						}
						temp = temp->next;
						}while(temp!=KH_X);
						
					}
					
					KH_X=customerMax_diff;
				}
				
				if(KH_new->energy >= KH_X->energy)
				{
					
					KH_new->next = KH_X->next;
					KH_new->prev = KH_X;
					KH_X->next->prev = KH_new;
					KH_X->next = KH_new;
				}
			
				else
				{
					
					KH_new->prev = KH_X->prev;
					KH_new->next = KH_X;
					KH_X->prev->next = KH_new;
					KH_X->prev = KH_new;
				}
			}
			KH_X = KH_new;
			size_KH_In_Desk ++;	
		}	
	
	}
	
	
	void print_dao_nguoc(DS_KH_Time* head)
	{
		if(head != nullptr){
			print_dao_nguoc(head->next);
			head->data->print();
		}
	}

	bool so_sanh_energy(customer* x, customer* y){
		if(abs(x->energy) > abs(y->energy)) return true;
		else if(abs(x->energy) < abs(y->energy)) return false;

		DS_KH_Time* tail = KH_Time_Tail;
		while(tail)
		{
			if(tail->data == x) return false;
			else if(tail->data == y) return true;
			tail = tail->prev;
		}
		return false;
	}
	void swap(customer* head, customer * tail)
	{
			
			customer* temp = new customer();
		
			temp->next=head->next;
			temp->prev=head->prev;
			head->next->prev = head->prev->next = temp;
	
			 	
			head->next=tail->next;
			head->prev=tail->prev;
			tail->next->prev = tail->prev->next = head;

			
			tail->next=temp->next;
			tail->prev=temp->prev;
			temp->next->prev = temp->prev->next = tail;
		

			delete temp;
	}	
	

	
	int sort(customer* head, int n, int incr) {
		int Dem = 0; 
	 
		 
		 for(int i = incr; i < n; i += incr)
		{
			for(int j = i; j >= incr; j -= incr)
			{
				customer* b = this->get_KH_At(head, j - incr);
				customer* a = this->get_KH_At(b, incr);

				if(so_sanh_energy(a,b))
				{
					this->swap(a, b);
					if(b == KH_Queue) KH_Queue = a;
					if(head == b) head = a;
					Dem++;
				}
				else break;
			}
		}	
		return Dem;
	}

	

public:	
	imp_res() {
		KH_X = KH_Queue =  nullptr;
		size_KH_Queue = size_KH_In_Desk = 0;
		KH_Time_Head = KH_Time_Tail = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void REVERSAL();
	void PURPLE();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);	

	~imp_res(){  
		while(KH_Time_Head)
		{
			DS_KH_Time* a = KH_Time_Head;	 
			KH_Time_Head = KH_Time_Head->next;
			delete a;
		}
	}
private:
	class DS_KH_Time{
	public:
		customer * data;
		DS_KH_Time* next;
		
		DS_KH_Time* prev;
		bool check_in_disk; 
	public:
		DS_KH_Time(customer * data, bool check_in_disk, DS_KH_Time* next = nullptr, DS_KH_Time* prev = nullptr)
		:data(data),next(next),prev(prev), check_in_disk(check_in_disk) {}
		~DS_KH_Time(){delete data;}
	};
};

void imp_res::RED(string name, int energy)
{
	
	if(energy == 0 ||size_KH_In_Desk + size_KH_Queue >= MAXSIZE * 2 ) return;


	else
	{
		customer* temp = KH_X;
				
				if (temp != nullptr) {
					do {
                		if (temp->name == name) {
              
                   			 return;
               			}
               		 	temp = temp->next;
						

            		} while (temp != KH_X);
					
        		}
				
			
				customer* temp2 = KH_Queue;
				if (temp2 != nullptr) {
           			do {
                		if (temp2->name == name) {
                   	
                   			 return;
               			}
               		 	temp2 = temp2->next;
            		} while (temp2 != KH_Queue);
        		}
	}

    if(size_KH_In_Desk == 0)
	{
		
		customer* KH_new = new customer(name, energy, nullptr, nullptr);
		KH_new->next = KH_new;
		KH_new->prev = KH_new;
		KH_X = KH_new;
		size_KH_In_Desk = 1;
				
		
		
		
		KH_Time_Tail = KH_Time_Head = new DS_KH_Time (KH_X, true);
		return;
	}
	
	if(size_KH_In_Desk == MAXSIZE)
	{
		
		customer* KH_new = new customer(name, energy, nullptr, nullptr);
		if(size_KH_Queue == 0)
		{
			
			KH_new->next = KH_new;
			KH_new->prev = KH_new;
			KH_Queue=KH_new;
		}
		
		else
		{
		
			KH_new->prev = KH_Queue->prev;
			KH_new->next = KH_Queue;
			KH_Queue->prev->next=KH_new;
			KH_Queue->prev = KH_new;
			
		}
		
		size_KH_Queue ++;
		

		 this->add_KH_to_DS_Time(KH_new,false);
	
		return;
	}
	
	
	

	customer* KH_new = new customer (name, energy, nullptr, nullptr);

	if(size_KH_In_Desk >= MAXSIZE / 2)
	{
				customer* temp; 
				temp = KH_X;
				
				customer* customerMax_diff = temp;
				
				int max_diff = 0;
				if(temp!=NULL){
					do{
					int res = abs(KH_new->energy - temp->energy);
					if (res > max_diff) {
						
						max_diff = res;
						customerMax_diff = temp;
						
					}
					temp = temp->next;
					}while(temp!=KH_X);
					
				}
				
				KH_X=customerMax_diff;
	}

	
	if(energy < KH_X->energy)
	{
		
		this->add_nghichKDH(KH_new);
	
	}
	
	else
	{
		this->add_thuanKDH(KH_new);
	
	}
	
	KH_X = KH_new;
	size_KH_In_Desk ++;

	this->add_KH_to_DS_Time(KH_new,true);
	
	return;
}

void imp_res::BLUE(int num)
{
	
	if(size_KH_In_Desk == 0) return;

	
	for(int i = 0; i < num && size_KH_In_Desk != 0; i++)
	{
		
		DS_KH_Time* KH_Xoa = this->find_KH_Xoa();

		
		this->delete_KH_Time(KH_Xoa);
	}


	this->insert_KH_FromQueueToDisk();
}

void imp_res::PURPLE()
	{
		if(this->size_KH_Queue<=1) return;
		int xoa = 0;

		DS_KH_Time* temp = KH_Time_Tail;
		DS_KH_Time* max = nullptr;
		for(int i = 0; i < size_KH_Queue + size_KH_In_Desk; i++)
		{
			if(temp->check_in_disk==0 && max==nullptr){
				max=temp;
			}else if(temp->check_in_disk==0 && abs(temp->data->energy)>abs(max->data->energy)){
				max=temp;
			}
			temp=temp->prev;
		}
		int n=1;
		customer* a = KH_Queue;
		while(a!=max->data){
			n++;
			a=a->next;
		}

		for(int i = n /2; i > 2; i /= 2)
		{
			for(int j = 0; j < i; j++)
			{
				xoa += sort(this->get_KH_At(KH_Queue, j), n - j, i);
			}
			
		}
		xoa += sort(KH_Queue, n, 1);
		        
		this->BLUE(xoa % MAXSIZE);
	}


void imp_res::DOMAIN_EXPANSION()
{
	
		DS_KH_Time* Thuatsi_Tail = nullptr; 
		DS_KH_Time* Oanlinh_Tail = nullptr; 
		DS_KH_Time* Thuatsi_Head = nullptr; 
		DS_KH_Time* Oanlinh_Head = nullptr; 

		if(size_KH_In_Desk == 0) return;

	
		int tong_Thuatsi = 0; 
		int tong_Oanhlinh = 0; 
		
			customer* temp = KH_X;
			for(int i=0;i<size_KH_In_Desk;i++){
				if(temp->energy>0){
					tong_Thuatsi+=temp->energy;
				}else{
					tong_Oanhlinh+=temp->energy;
				}
				temp=temp->next;
			}

			
			temp = KH_Queue;
			for(int i=0;i<size_KH_Queue;i++){
				if(temp->energy>0){
					tong_Thuatsi+=temp->energy;
				}else{
					tong_Oanhlinh+=temp->energy;
				}
				temp=temp->next;
			}

	

		
	
		DS_KH_Time* temp_tgian = KH_Time_Head;
		for(int i = 0; i < size_KH_In_Desk + size_KH_Queue; i++)
		{
			
			if(temp_tgian->data->energy > 0)
			{
				
				if(Thuatsi_Head == nullptr)
				{
					
						Thuatsi_Head = temp_tgian;
						Thuatsi_Tail = temp_tgian;
						
				}
				else
				{
					
					Thuatsi_Tail->next=temp_tgian;
					temp_tgian->prev=Thuatsi_Tail;
					Thuatsi_Tail=temp_tgian;
				}
				
			}
			
			
			else
			{
				if(Oanlinh_Head == nullptr)
				{
					
						Oanlinh_Head = temp_tgian;
						Oanlinh_Tail = temp_tgian;
				}
				else
				{
					
					Oanlinh_Tail->next=temp_tgian;
					temp_tgian->prev=Oanlinh_Tail;
					Oanlinh_Tail = temp_tgian;
				}
			}

			temp_tgian =temp_tgian->next;
		}

	
	
		if(Oanlinh_Head != nullptr) Oanlinh_Head->prev = Oanlinh_Tail->next = nullptr;
		if(Thuatsi_Head != nullptr) Thuatsi_Head->prev = Thuatsi_Tail->next = nullptr;
		
		if(abs(tong_Oanhlinh) <= tong_Thuatsi)
		{
			print_dao_nguoc(Oanlinh_Head);
			while(Oanlinh_Head != nullptr)
			{
				DS_KH_Time* KH_Xoa;
				
				KH_Xoa=Oanlinh_Head;
				Oanlinh_Head=Oanlinh_Head->next;

				
				this->delete_KH_Time(KH_Xoa);
			}

			
			KH_Time_Head = Thuatsi_Head;
			KH_Time_Tail = Thuatsi_Tail;
		}
	
		else{
			print_dao_nguoc(Thuatsi_Head);
			while(Thuatsi_Head != nullptr)
			{
				
				DS_KH_Time* KH_Xoa;
				
				KH_Xoa=Thuatsi_Head;
				Thuatsi_Head=Thuatsi_Head->next;
				
				this->delete_KH_Time(KH_Xoa);
				
			}
			
			KH_Time_Head = Oanlinh_Head;
			KH_Time_Tail = Oanlinh_Tail;
		}

	
		this->insert_KH_FromQueueToDisk();
}
void imp_res::REVERSAL()
{
	
			if(size_KH_In_Desk <= 1) return;			


			customer* head = nullptr; 
			customer* tail = nullptr;
			
			customer* head_W = this->reverse_HEAD(KH_X, 1); 
			customer* tail_W = this->reverse_TAIL(KH_X->next, 1); 

		
			head = this->reverse_HEAD(KH_X, -1); 
			tail = this->reverse_TAIL(KH_X->next, -1); 
			if(head->energy < 0){
				while(head != tail)
				{
					this->swap(head, tail);
					customer* temp = head;
					head = tail;
					tail = temp;

					head = this->reverse_HEAD(head->prev, - 1);
					if(head == tail) break;		
					tail = this->reverse_TAIL(tail->next, - 1);
				}
			}

		
			if(head_W->energy > 0){
				while(head_W != tail_W)
				{
					
					this->swap(head_W, tail_W);
					customer* temp = head_W;
					head_W = tail_W;
					tail_W = temp;

					head_W = this->reverse_HEAD(head_W->prev, 1);
					if(head_W == tail_W) break;		
					tail_W = this->reverse_TAIL(tail_W->next, 1);
				}
			}
}

void imp_res::UNLIMITED_VOID()
{
	 int tong_Min = 2147483633; 
	if(size_KH_In_Desk <= 3) return;

			
			customer* head = nullptr, * tail = nullptr; 
			int size_max=0;
			
			customer* a = KH_X; 
			for(int i = 0; i < size_KH_In_Desk; i++)
			{
				int tong = 0;  
				customer* b = a; 
				for(int j = 0; j < size_KH_In_Desk; j++)
				{
				
					tong += b->energy;
					if((tong_Min>tong || tong_Min==tong && j+1>=size_max) && j>=3){
						tong_Min=tong;
						head=a;
						tail=b;
						size_max=j+1;
					}
					
					b = b->next;
				}
				a = a->next;
			}			
		
			
			customer* min = head; 
			customer* tam = head->next; 
			
			int size_HeadToMin = 1, size_HeadToTail = 1;
			
		
			while(tam != tail->next)
			{
			
					size_HeadToTail++;
					
				if(tam->energy < min->energy) {
					
        			min = tam; 
					
       				size_HeadToMin = size_HeadToTail; 
					
					
   				 }
				tam = tam->next; 
			}
			
			 
			
			for(int i = 0; i <= size_HeadToTail - size_HeadToMin; i++)
			{	
				
				min->print();	
				min=min->next;
				
			}
			
		
			for(int i = 0; i < size_HeadToMin-1 ; i++)
			{

				head->print();
				head=head->next;

			}
}
void imp_res::LIGHT(int num)
{
			int cnt2=size_KH_In_Desk;
			int cnt1=size_KH_Queue;
			if(num == 0 )
			{
				
				
				customer* temp = KH_Queue;
				
				while(cnt1!=0){
					temp->print();
					temp = temp->next;
					cnt1--;
				}
					
				

			}
			
			else if (num > 0)
			{	
			
				customer* temp = KH_X;
				
				while(cnt2!=0){
					
					temp->print();
					temp = temp->next;
					cnt2--;
				}	
				
			}
			
			else	
			{
			
				customer* temp = KH_X;
					while(cnt2!=0){
				
					temp->print();
					temp = temp->prev;
					cnt2--;
				}
			
			}
}