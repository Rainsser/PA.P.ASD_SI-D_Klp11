#include <iostream>
#include <stdio.h>
using namespace std;

struct Tugas {
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

int inputAngka() {
	int x;
	while(!(cin >> x)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Input harus angka\n";
	}
	return x;
}

char namaFile[] = "tugas.txt";

void bacaFile(){
	FILE *fp = fopen(namaFile,"r");
	n = 0;
	
	if(fp == NULL){
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

void simpanFile() {
	FILE *fp = fopen(namaFile, "w");
	
	if(fp == NULL) {
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

void inputTugas() {
	int jumlah;
	
	bacaFile();
	
	cout << "============================\n";
	cout << "\nINPUT TUGAS\n";
	cout << "============================\n";
	cout << "\nMasukkan jumlah data Tugas: ";
	jumlah = inputAngka();
	if(jumlah <= 0) return;
	
	cin.ignore();
	
	for(int i = 0; i < jumlah; i++) {
		cout << "\nID Tugas : " << n+1 << endl;
		data[n].id = n+1;
		
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
		cin.ignore();
		cout << "Tugas berhasil ditambahkan!\n";
	}
	
	char ulang;
	cout << "\nData telah tersimpan\n";
	cout << "Kembali ke menu? (y/n): ";
	cin >> ulang;
}

void lihatTugas(){
}

void cariTugas(){
}

void editTugas(){
}

void ubahStatus(){
}

void hapusTugas(){
}

void menuUtama(){
	int pilih;
	do {
		cout << "\n==============================\n";
		cout << "        Selamat Datang!\n";
		cout << "==============================\n";
		cout << "1. Input Tugas\n";
		cout << "2. Lihat Tugas\n";
		cout << "3. Cari Tugas\n";
		cout << "4. Edit Tugas\n";
		cout << "5. Ubah Status Tugas\n";
		cout << "6. Hapus Tugas\n";
		cout << "7. Logout\n";
		cout << "Masukkan menu: ";
		
		pilih = inputAngka();
		
		if(pilih == 1) inputTugas();
		else if(pilih == 2) lihatTugas();
		else if(pilih == 3) cariTugas();
		else if(pilih == 4) editTugas();
		else if(pilih == 5) ubahStatus();
		else if(pilih == 6) hapusTugas();
		
	} while(pilih != 7);
	
	cout << "\nTerima kasih, sampai jumpa User!\n";
}

int main(){
	char user[20], pass[20];
	
	cout << "\n========================================\n";
	cout << "               Halo User!\n";
	cout << "Silahkan login untuk masuk ke menu utama\n";
	cout << "=============================================\n";
	
	cout << "Masukkan Username: "; cin >> user;
	cout << "Masukkan Password: "; cin >> pass;
	
	int userbenar = (user[0] == 'r' && user[1] == 'a' && user[2] == 'i' && user[3] == 's' && user[4] == 's' && user[5] == 'a' && user[6] == '\0') || (user[0] == 'l' && user[1] == 'i' && user[2] == 'n' && user[3] == 'd' && user[4] == 'a' && user[5] == '\0');
	int pwdbenar = (pass[0] == '0' && pass[1] == '7' && pass[2] == '7' && pass[3] == '\0') || (pass[0] == '0' && pass[1] == '8' && pass[2] == '3' && pass[3] == '\0');
	
	if(userbenar && pwdbenar) {
		menuUtama();
	} else {
		cout << "Login gagal - username atau password salah\n";
	}

}
