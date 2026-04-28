#include <iostream>
#include <stdio.h>
using namespace std;

struct Tugas
{
	int id;
	char judul[100];
	char deskripsi[200];
	int tgl_dl;
	int bulan_dl;
	int tahun_dl;
	int prioritas;
	int status;
};

Tugas data[100];
int n = 0;

int bandingkan(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return a[i] - b[i];
		}
		i++;
	}
	return a[i] - b[i];
}

int inputAngka()
{
	int x;
	while (!(cin >> x))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Input harus angka\n";
	}
	return x;
}

char namaFile[] = "tugas.txt";

void bacaFile()
{
	FILE *fp = fopen(namaFile, "r");
	n = 0;

	if (fp == NULL)
	{
		return;
	}
	
	while(fscanf(fp, "%d %s %s %d %d %d %d %d",
		&data[n].id, data[n].judul,
		data[n].deskripsi, &data[n].tgl_dl,
		&data[n].bulan_dl, &data[n].tahun_dl,
		&data[n].prioritas, &data[n].status) != EOF) {
			
		n++;
	}

	fclose(fp);
}

void simpanFile()
{
	FILE *fp = fopen(namaFile, "w");

	if (fp == NULL)
	{
		cout << "Gagal membuka file\n";
		return;
	}
	
	for(int i = 0; i < n; i++) {
		fprintf(fp, "%d %s %s %d %d %d %d %d\n",
			data[i].id, data[i].judul,
			data[i].deskripsi, data[i].tgl_dl,
			data[i].bulan_dl, data[i].tahun_dl,
			data[i].prioritas, data[i].status);
	}

	fclose(fp);
}

void inputTugas()
{
	int jumlah;

	bacaFile();

	cout << "============================\n";
	cout << "\nINPUT TUGAS\n";
	cout << "============================\n";
	cout << "\nMasukkan jumlah data Tugas: ";
	jumlah = inputAngka();
	if (jumlah <= 0)
		return;

	cin.ignore();

	for (int i = 0; i < jumlah; i++)
	{
		cout << "\nID Tugas : " << n + 1 << endl;
		data[n].id = n + 1;

		cout << "Judul Tugas : ";
		cin.getline(data[n].judul, 100);

		cout << "Deskripsi: ";
		cin.getline(data[n].deskripsi, 200);

		cout << "Tanggal Deadline: ";
		data[n].tgl_dl = inputAngka();

		cout << "Bulan Deadline (1-12): ";
		data[n].bulan_dl = inputAngka();

		cout << "Tahun Deadline: ";
		data[n].tahun_dl = inputAngka();

		cout << "Prioritas (1=tinggi, 2=sedang, 3=rendah):";
		data[n].prioritas = inputAngka();

		data[n].status = 0;

		n++;

		simpanFile();
		cin.ignore();
		cout << "Tugas berhasil ditambahkan!\n";
	}

	char ulang;
	cout << "\nData telah tersimpan\n";
	cout << "Kembali ke menu? (y/n): ";
	cin >> ulang;
}

void bubbleSort(struct Tugas data[], int jumlah){
	int i, j;
	struct Tugas temp;

	for (i = 0; i < jumlah - 1; i++){
		for (j = 0; j < jumlah - i - 1; j++){
			if (data[j].prioritas > data[j + 1].prioritas){
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}
}

void quickSort(struct Tugas data[], int low, int high){
	int i = low, j = high;
	int pivot = data[(low+high)/2].prioritas;

	while(i <= j){
		while(data[i].prioritas > pivot) i++;
		while(data[j].prioritas < pivot) j--;

		if(i <= j){
			Tugas temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			i++;
			j--;
		}
	}
	if (low < j) quickSort(data, low, j);
	if (i < high) quickSort(data, i, high);
}

void sequentialSearch(char x[])
{
	bool ditemukan = false;
	for (int i = 0; i < n; i++)
	{
		if (bandingkan(data[i].judul, x) == 0)
		{
			cout << "Tugas ditemukan:\n";
			cout << "Id tugas = " << data[i].id << endl;
			cout << "Judul tugas = " << data[i].judul << endl;
			cout << "Deskripsi = " << data[i].deskripsi << endl;
			cout << "Tanggal Deadline = " << data[i].tgl_dl << "/" << data[i].bulan_dl << "/" << data[i].tahun_dl << endl;
			cout << "Prioritas = " << data[i].prioritas << endl;
			cout << "Status = " << (data[i].status == 0 ? "Belum Selesai" : "Selesai") << endl;
			ditemukan = true;
			break;
		}
	}
	if (!ditemukan)
	{
		cout << "Tugas tidak ditemukan.\n";
	}
}
void binarySearch(char x[]) {
    bool ditemukan = false;

    int i = 0;        // awal
    int j = n - 1;    // akhir

    // manggil void sort data harus urut dulu

    while (i <= j) {
        int k = (i + j) / 2;  // tengah

        int hasil = bandingkan(data[k].judul, x);

        if (hasil == 0) {
            cout << "Tugas ditemukan:\n";
			cout << "Id tugas = " << data[k].id << endl;
			cout << "Judul tugas = " << data[k].judul << endl;
			cout << "Deskripsi = " << data[k].deskripsi << endl;
			cout << "Tanggal Deadline = " << data[k].tgl_dl << "/" << data[k].bulan_dl << "/" << data[k].tahun_dl << endl;
			cout << "Prioritas = " << data[k].prioritas << endl;
			cout << "Status = " << (data[k].status == 0 ? "Belum Selesai" : "Selesai") << endl;
            ditemukan = true;
            break;
        } 
        else if (hasil < 0) {
            i = k + 1;  // geser ke kanan
        } 
        else {
            j = k - 1;  // geser ke kiri
        }
    }

    if (!ditemukan) {
        cout << "Tugas tidak ditemukan\n";
    }
}

void tampilData(){
	for(int i = 0; i < n; i++){
		cout << "\nID Tugas: " << data[i].id;
		cout << "\nJudul Tugas: " << data[i].judul;
		cout << "\nDeskripsi: " << data[i].deskripsi;
		cout << "\nTanggal Deadline: " << data[i].tgl_dl; 
		cout << "\nBulan Deadline: " << data[i].bulan_dl;
		cout << "\nTahun Deadline: " << data[i].tahun_dl;
		cout << "\nPrioritas: " << data[i].prioritas;
		cout << "\nStatus: " << data[i].status << endl;
	}
}

void lihatTugas(){
	bacaFile();
	int jumlah = n;

	cout << "============================\n";
	cout << "\nLIHAT TUGAS\n";
	cout << "============================\n";
	if(n == 0) {
		cout << "\nData kosong\n";
		return;
	}
	cout << "\nJumlah Data Tugas : " << n << endl;
	cout << "Pilih Metode Lihat:\n";
	cout << "1. Ascending\n";
	cout << "2. Descending\n";
	cout << "Masukkan metode: ";
	
	int pilih = inputAngka();
	
	if(pilih == 1) {
		bubbleSort(data, jumlah);
		tampilData();
	}
	else if(pilih == 2) {
		quickSort(data, 0, jumlah - 1);
		tampilData();
	}
	
	cout << "\nPress any key to continue . . .";
	cin.ignore();
	cin.get();
}

void cariTugas()
{
	// menu cari tugas di dalamnya ada menu lagi untuk pencarian sequential dan binary search
	int metode;
	bacaFile();
	char judulCari[100];
	cout << "============================\n";
	cout << "\n CARI TUGAS\n";
	cout << "============================\n";
	cout << "1. Sequential Search\n";
	cout << "2. Binary Search\n";
	cout << "Masukkan judul tugas yang ingin dicari: ";
	cin.ignore();
	cin.getline(judulCari, 100);

	cout << "Pilih metode pencarian: ";
	cin >> metode;
	metode = inputAngka();
	if (metode == 1)
	{
		sequentialSearch(judulCari);
	}
	else if (metode == 2)
	{
		binarySearch(judulCari);
	}
	else
	{
		cout << "Metode tidak valid\n";
	}
}

void editTugas()
{
    bacaFile();
    // Node single linked list
    struct Node {
        Tugas data;
        Node* next;
    };

    Node* head = NULL;

	int id;
	cout << "\nMasukkan ID roti yang mau diedit: ";
	id = inputAngka();

	for(int i = 0; i < n; i++){
		if(data[i].id == id){
			cout << "Data ditemukan\n";
			
			cout << "=====================\n";
			cout << "Data lama:\n";
			cout << "\nJudul Tugas: " << data[i].judul << endl;
			cout << "\nDeskripsi: " << data[i].deskripsi << endl;
			cout << "\nTanggal Deadline: " << data[i].tgl_dl << endl; 
			cout << "\nBulan Deadline: " << data[i].bulan_dl << endl;
			cout << "\nTahun Deadline: " << data[i].tahun_dl << endl;
			cout << "\nPrioritas: " << data[i].prioritas << endl;
			cout << "\nStatus: " << data[i].status << endl;

			cout << "=====================\n";
			cout << "Data baru:\n";
			cout << "\nJudul Tugas: "; cin >> data[i].judul;
			cout << "\nDeskripsi: "; cin >> data[i].deskripsi;
			cout << "\nTanggal Deadline: "; cin >> data[i].tgl_dl; 
			cout << "\nBulan Deadline: "; cin >> data[i].bulan_dl;
			cout << "\nTahun Deadline: "; cin >> data[i].tahun_dl;
			cout << "\nPrioritas: "; cin >> data[i].prioritas;
			cout << "\nStatus: "; cin >> data[i].status;

			simpanFile();

			cout << "\nData tugas berhasil diperbarui\n";
			cout << "Press any key to continue . . .";
			cin.ignore();
			cin.get();
			return;
		}
	}
	cout << "Data tidak ditemukan\n";
}

void ubahStatus()
{
    bacaFile();
    // Node double linked list
    struct Node {
        Tugas data;
        Node* next;
        Node* prev;
    };
    Node* head = NULL;

    // Membentuk double linked list dari array
    for (int i = 0; i < n; i++)
    {
        Node* baru = new Node;
        baru->data = data[i];
        baru->next = NULL;
        baru->prev = NULL;

        if (head == NULL)
            head = baru;
        else
        {
            Node* temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = baru;
            baru->prev = temp; // ciri double (punya prev)
        }
    }

    int id;
    cout << "Masukkan ID tugas: ";
    id = inputAngka();

    Node* temp = head;
    bool ditemukan = false;
 
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            cout << "Ubah status (0=Belum, 1=Selesai): ";
            temp->data.status = inputAngka();

            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan)
        cout << "Tugas tidak ditemukan\n";

    temp = head;
    int i = 0;
    while (temp != NULL)
    {
        data[i++] = temp->data;
        temp = temp->next;
    }

    simpanFile();
    cout << "Status berhasil diubah!\n";
}

void hapusTugas()
{
    bacaFile();
    struct Node {
        Tugas data;
        Node* next;
    };

    Node* head = NULL;
    Node* tail = NULL;
 
    for (int i = 0; i < n; i++)
    {
        Node* baru = new Node;
        baru->data = data[i];
        baru->next = NULL;

        if (head == NULL)
        {
            head = tail = baru;
        }
        else
        {
            tail->next = baru;
            tail = baru; // update tail
        }
    }

    int id;
    cout << "Masukkan ID yang ingin dihapus: ";
    id = inputAngka();

    Node* temp = head;
    Node* prev = NULL;

    // Proses hapus node
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            // jika di head
            if (temp == head)
                head = head->next;

            // jika di tengah / akhir
            else
                prev->next = temp->next;

            // jika di tail
            if (temp == tail)
                tail = prev;

            delete temp;
            cout << "Tugas berhasil dihapus\n";
            break;
        }

        prev = temp;
        temp = temp->next;
    }
 
    // Balik ke array
    temp = head;
    n = 0;
    while (temp != NULL)
    {
        data[n++] = temp->data;
        temp = temp->next;
    }

    simpanFile();
}

void menuUtama()
{
	int pilih;
	do
	{
		cout << "\n==============================\n";
		cout << "        Selamat Datang!\n";
		cout << "==============================\n";
		cout << "1. Input Tugas\n";
		cout << "2. Lihat Tugas(dengan sorting)\n";
		cout << "3. Cari Tugas\n";
		cout << "4. Edit Tugas(	Sisip Data Single Linked list)\n";
		cout << "5. Ubah Status Tugas(Double Linked list)\n";
		cout << "6. Hapus Tugas(Linked list kepala ekor)\n";
		cout << "7. Logout\n";
		cout << "Masukkan menu: ";

		pilih = inputAngka();

		if (pilih == 1)
			inputTugas();
		else if (pilih == 2)
			lihatTugas();
		else if (pilih == 3)
			cariTugas();
		else if (pilih == 4)
			editTugas();
		else if (pilih == 5)
			ubahStatus();
		else if (pilih == 6)
			hapusTugas();

	} while (pilih != 7);

	cout << "\nTerima kasih, sampai jumpa User!\n";
}

int main()
{
	char user[20], pass[20];

	cout << "\n========================================\n";
	cout << "               Halo User!\n";
	cout << "Silahkan login untuk masuk ke menu utama\n";
	cout << "=============================================\n";

	cout << "Masukkan Username: ";
	cin >> user;
	cout << "Masukkan Password: ";
	cin >> pass;

	int userbenar = (user[0] == 'r' && user[1] == 'a' && user[2] == 'i' && user[3] == 's' && user[4] == 's' && user[5] == 'a' && user[6] == '\0') || (user[0] == 'l' && user[1] == 'i' && user[2] == 'n' && user[3] == 'd' && user[4] == 'a' && user[5] == '\0');
	int pwdbenar = (pass[0] == '0' && pass[1] == '7' && pass[2] == '7' && pass[3] == '\0') || (pass[0] == '0' && pass[1] == '8' && pass[2] == '3' && pass[3] == '\0');

	if (userbenar && pwdbenar)
	{
		menuUtama();
	}
	else
	{
		cout << "Login gagal - username atau password salah\n";
	}
}
