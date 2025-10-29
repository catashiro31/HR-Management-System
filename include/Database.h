#pragma once
#include <vector>
#include <string>
#include <map>
#include "NhanVien.h" // Giả sử chứa tất cả các lớp con
#include "PhongBan.h"
#include "ChucDanh.h"
#include "LichSuThayDoi.h"
#include "PhucLoi.h" 

// Lớp Database quản lý toàn bộ dữ liệu của hệ thống
class Database {
private:
    // === DỮ LIỆU ===
    std::vector<NhanVien*> dsNhanVien;
    std::vector<PhongBan> dsPhongBan;
    std::vector<ChucDanh> dsChucDanh; // Chỉ 1 lần
    std::map<std::string, std::vector<LichSuThayDoi>> dsLichSu; 
    std::vector<PhucLoi> danhSachPhucLoi; // Đổi tên từ dsPhucLoi để khớp file .cpp
    std::map<std::string, std::vector<std::string>> danhSachDangKyPhucLoi;

    // === CẤU HÌNH FILE ===
    // (Những hằng số này nên ở GlobalConfig.h, nhưng tôi giữ lại theo file của bạn)
    const std::string FILE_NHANVIEN = "../Stored/nhanvien.csv";
    const std::string FILE_PHONGBAN = "../Stored/phongban.csv";
    const std::string FILE_CHUCDANH = "../Stored/chucdanh.csv";
    const std::string FILE_LICHSU = "../Stored/lichsu.csv"; 
    const std::string FILE_PHUCLOI = "../Stored/phucloi.csv";
    const std::string FILE_DANGKY_PHUCLOI = "../Stored/nhanvien_phucloi.csv";

    int autoIncrementMaNV; 

    // === HÀM HỖ TRỢ TẢI/LƯU ===
    NhanVien* taoNhanVienTuLoai(LoaiNhanVien loai);
    std::string taoMaNVMoi();

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
    NhanVien* timNhanVienTheoMa(const std::string& maNV);
    bool xoaNhanVienTheoMa(const std::string& maNV);
    const std::vector<NhanVien*>& getDSNhanVien() const;

    // --- Các hàm Quản lý Phòng Ban ---
    void themPhongBan(const PhongBan& pb);
    PhongBan* timPhongBanTheoMa(const std::string& maPB);
    const std::vector<PhongBan>& getDSPhongBan() const;
    
    // --- Các hàm Quản lý Chức Danh ---
    void themChucDanh(const ChucDanh& cd); // Chỉ 1 lần
    ChucDanh* timChucDanhTheoMa(const std::string& maCD); // Chỉ 1 lần
    const std::vector<ChucDanh>& getDSChucDanh() const; // Chỉ 1 lần

    // --- Các hàm Quản lý Lịch Sử --- 
    void themGhiNhanLichSu(const std::string& maNV, const std::string& moTa, const std::string& giaTriCu, const std::string& giaTriMoi);
    const std::vector<LichSuThayDoi>* layLichSuCuaNV(const std::string& maNV) const;

    // --- CAC HAM MOI CHO PHUC LOI ---
    const std::vector<PhucLoi>& getDSPhucLoi() const;
    PhucLoi* timPhucLoiTheoMa(const std::string& maPL);
    void themPhucLoi(const PhucLoi& pl);
    void xoaPhucLoi(const std::string& maPL);
    std::vector<PhucLoi*> getPhucLoiCuaNhanVien(const std::string& maNV);
    bool ghiDanhPhucLoi(const std::string& maNV, const std::string& maPL);
    bool huyGhiDanhPhucLoi(const std::string& maNV, const std::string& maPL);
};

