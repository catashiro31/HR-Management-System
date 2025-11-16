#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "Database.h"
#include "Account.h" 
#include <map>

class QuanLyNhanSu {
private:
    Database db;
    Account* currentUser; // Lưu người dùng đang đăng nhập
    bool dangChay;

    // === HÀM KHỞI CHẠY HỆ THỐNG ===
    bool dangNhap();
    void hienThiMenuChinh();
    void thoatChuongTrinh();

    // === MENU & XỬ LÝ THEO VAI TRÒ ===
    void hienThiMenuChuTich();
    void xuLyMenuChuTich(bool* dangXuat);
    void hienThiMenuTruongPhong();
    void xuLyMenuTruongPhong(bool* dangXuat);
    void hienThiMenuKeToan();
    void xuLyMenuKeToan(bool* dangXuat);
    void hienThiMenuNhanVien();
    void xuLyMenuNhanVien(bool* dangXuat);

    // === CÁC CHỨC NĂNG (TÁI SỬ DỤNG) ===
    
    // Chức năng Hồ sơ
    void chucNang_ThemNhanVien();
    void chucNang_CapNhatNhanVien();
    void chucNang_QuanLyTrangThai();
    // --- DÒNG CẦN SỬA LÀ ĐÂY ---
    void chucNang_ThayDoiVaiTro(NhanVien* nv); // Phải có (NhanVien* nv)

    // Chức năng Xem
    void chucNang_XemDanhSach();
    void chucNang_XemDanhSach_Sort();
    void chucNang_TimKiemNhanVien(string maNV = ""); 
    void chucNang_XemLichSuThayDoi();

    // Chức năng Tổ chức
    void chucNang_QuanLyPhongBan();
    void chucNang_QuanLyChucDanh(); 
    void chucNang_ThemChucDanh(); 
    void chucNang_XemChucDanh(); 

    // Chức năng Lương & Phúc lợi
    void chucNang_QuanLyPhucLoi();
    void chucNang_ChayBangLuong();
    void chucNang_QuanLyGoiPhucLoi(); 
    void chucNang_GhiDanhPhucLoi(); 
    void chucNang_XemGoiPhucLoi(); 
    void chucNang_ThemGoiPhucLoi(); 
    void chucNang_XoaGoiPhucLoi(); 

    // Chức năng Báo cáo
    void chucNang_BaoCaoNhanSuTheoPhongBan();
    void chucNang_XuatDanhSachNhanVien();


public:
    QuanLyNhanSu();
    void khoiChay(); 
};

#endif