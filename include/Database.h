#pragma once
#include <vector>
#include <string>
#include <map>
#include "NhanVien.h" // Giả sử chứa tất cả các lớp con
#include "PhongBan.h"
#include "ChucDanh.h"
#include "LichSuThayDoi.h"
#include "PhucLoi.h" 
using namespace std;


// Lớp Database quản lý toàn bộ dữ liệu của hệ thống
class Database {
private:
    // === DỮ LIỆU ===
    vector<NhanVien*> dsNhanVien;
    vector<PhongBan> dsPhongBan;
    vector<ChucDanh> dsChucDanh; // Chỉ 1 lần
    map<string, vector<LichSuThayDoi>> dsLichSu; 
    vector<PhucLoi> danhSachPhucLoi; // Đổi tên từ dsPhucLoi để khớp file .cpp
    map<string, vector<string>> danhSachDangKyPhucLoi;

    // === CẤU HÌNH FILE ===
    // (Những hằng số này nên ở GlobalConfig.h, nhưng tôi giữ lại theo file của bạn)
    const string FILE_NHANVIEN = "../Stored/nhanvien.csv";
    const string FILE_PHONGBAN = "../Stored/phongban.csv";
    const string FILE_CHUCDANH = "../Stored/chucdanh.csv";
    const string FILE_LICHSU = "../Stored/lichsu.csv"; 
    const string FILE_PHUCLOI = "../Stored/phucloi.csv";
    const string FILE_DANGKY_PHUCLOI = "../Stored/nhanvien_phucloi.csv";

    int autoIncrementMaNV; 

    // === HÀM HỖ TRỢ TẢI/LƯU ===
    NhanVien* taoNhanVienTuLoai(LoaiNhanVien loai);
    string taoMaNVMoi();

    // Các hàm riêng tư để tải/lưu từng file cụ thể
    void taiNhanVien();
    void luuNhanVien() const;
    void taiPhongBan();
    void luuPhongBan() const;
    void taiChucDanh(); // Chỉ 1 lần
    void luuChucDanh() const; // Chỉ 1 lần
    void taiLichSu();   
    void luuLichSu() const; 
    void taiPhucLoi(); // Chỉ 1 lần
    void luuPhucLoi(); // Chỉ 1 lần
    void taiDangKyPhucLoi(); // Chỉ 1 lần
    void luuDangKyPhucLoi(); // Chỉ 1 lần

public:
    Database();
    ~Database();

    // --- Các hàm Tải và Lưu file ---
    void taiDuLieuTuFile();
    void luuDuLieuVaoFile();

    // --- Các hàm Quản lý Nhân Viên (CRUD) ---
    void themNhanVien(NhanVien* nv);
    NhanVien* timNhanVienTheoMa(const string& maNV);
    bool xoaNhanVienTheoMa(const string& maNV);
    const vector<NhanVien*>& getDSNhanVien() const;

    // --- Các hàm Quản lý Phòng Ban ---
    void themPhongBan(const PhongBan& pb);
    PhongBan* timPhongBanTheoMa(const string& maPB);
    const vector<PhongBan>& getDSPhongBan() const;
    
    // --- Các hàm Quản lý Chức Danh ---
    void themChucDanh(const ChucDanh& cd); // Chỉ 1 lần
    ChucDanh* timChucDanhTheoMa(const string& maCD); // Chỉ 1 lần
    const vector<ChucDanh>& getDSChucDanh() const; // Chỉ 1 lần

    // --- Các hàm Quản lý Lịch Sử --- 
    void themGhiNhanLichSu(const string& maNV, const string& moTa, const string& giaTriCu, const string& giaTriMoi);
    const vector<LichSuThayDoi>* layLichSuCuaNV(const string& maNV) const;

    // --- CAC HAM MOI CHO PHUC LOI ---
    const vector<PhucLoi>& getDSPhucLoi() const;
    PhucLoi* timPhucLoiTheoMa(const string& maPL);
    void themPhucLoi(const PhucLoi& pl);
    void xoaPhucLoi(const string& maPL);
    vector<PhucLoi*> getPhucLoiCuaNhanVien(const string& maNV);
    bool ghiDanhPhucLoi(const string& maNV, const string& maPL);
    bool huyGhiDanhPhucLoi(const string& maNV, const string& maPL);
};

