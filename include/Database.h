#pragma once
#include <vector>
#include <string>
#include <map>
#include "NhanVien.h" 
#include "PhongBan.h"
#include "ChucDanh.h"
#include "LichSuThayDoi.h"
#include "PhucLoi.h" 
#include "Account.h" 
using namespace std;


class Database {
private:
    // === DỮ LIỆU ===
    vector<NhanVien*> dsNhanVien;
    vector<PhongBan> dsPhongBan;
    vector<ChucDanh> dsChucDanh; 
    map<string, vector<LichSuThayDoi>> dsLichSu; 
    vector<PhucLoi> danhSachPhucLoi;
    map<string, vector<string>> danhSachDangKyPhucLoi;
    vector<Account*> dsTaiKhoan; 

    // === CẤU HÌNH FILE ===
    const string FILE_NHANVIEN = "nhanvien.csv";
    const string FILE_PHONGBAN = "phongban.csv";
    const string FILE_CHUCDANH = "chucdanh.csv";
    const string FILE_LICHSU = "lichsu.csv"; 
    const string FILE_PHUCLOI = "phucloi.csv";
    const string FILE_DANGKY_PHUCLOI = "nhanvien_phucloi.csv";
    const string FILE_ACCOUNT = "accounts.csv"; 

    int autoIncrementMaNV; 

    // === HÀM HỖ TRỢ TẢI/LƯU ===
    NhanVien* taoNhanVienTuLoai(LoaiNhanVien loai);
    string taoMaNVMoi();
    void taiNhanVien();
    void luuNhanVien() const;
    void taiPhongBan();
    void luuPhongBan() const;
    void taiChucDanh();
    void luuChucDanh() const;
    void taiLichSu();   
    void luuLichSu() const; 
    void taiPhucLoi();
    void luuPhucLoi();
    void taiDangKyPhucLoi();
    void luuDangKyPhucLoi();
    void taiTaiKhoan(); 
    void luuTaiKhoan() const; 
    
    void kiemTraTaiKhoanChuTich();
    
    // --- THÊM DÒNG NÀY VÀO ---
    bool tenEmailDaTonTai(const string& email) const;
    // --- KẾT THÚC ---

public:
    Database();
    ~Database();

    // --- Tải và Lưu file ---
    void taiDuLieuTuFile();
    void luuDuLieuVaoFile();

    // --- Quản lý Tài khoản ---
    Account* xacThucNguoiDung(const string& username, const string& password);
    void taoTaiKhoanTuDong(NhanVien* nv, Role role);

    // --- Các hàm Quản lý Nhân Viên (CRUD) ---
    void themNhanVien(NhanVien* nv, Role role); 
    NhanVien* timNhanVienTheoMa(const string& maNV);
    bool xoaNhanVienTheoMa(const string& maNV);
    const vector<NhanVien*>& getDSNhanVien() const;

    // ... (Các hàm khác giữ nguyên) ...
    void themPhongBan(const PhongBan& pb);
    PhongBan* timPhongBanTheoMa(const string& maPB);
    const vector<PhongBan>& getDSPhongBan() const;
    void themChucDanh(const ChucDanh& cd); 
    ChucDanh* timChucDanhTheoMa(const string& maCD); 
    const vector<ChucDanh>& getDSChucDanh() const; 
    void themGhiNhanLichSu(const string& maNV, const string& moTa, const string& giaTriCu, const string& giaTriMoi);
    const vector<LichSuThayDoi>* layLichSuCuaNV(const string& maNV) const;
    const vector<PhucLoi>& getDSPhucLoi() const;
    PhucLoi* timPhucLoiTheoMa(const string& maPL);
    void themPhucLoi(const PhucLoi& pl);
    void xoaPhucLoi(const string& maPL);
    vector<PhucLoi*> getPhucLoiCuaNhanVien(const string& maNV);
    bool ghiDanhPhucLoi(const string& maNV, const string& maPL);
    bool huyGhiDanhPhucLoi(const string& maNV, const string& maPL);
    Account* timTaiKhoanTheoMaNV(const string& maNV);
    void capNhatVaiTro(NhanVien* nv, Account* acc, Role vaiTroMoi);
    Account* timTaiKhoanDauTienTheoVaiTro(Role role);
};