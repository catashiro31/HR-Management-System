#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "Database.h"
#include "Account.h" // <-- THÊM VÀO
#include <map>

class QuanLyNhanSu {
private:
    Database db;
    Account* currentUser; // <-- THAY ĐỔI: Lưu người dùng hiện tại
    bool dangChay;

    // === HÀM KHỞI CHẠY HỆ THỐNG ===
    bool dangNhap();
    void hienThiMenuChinh();
    void thoatChuongTrinh();

    // === MENU & XỬ LÝ THEO VAI TRÒ ===
    // [1] CHỦ TỊCH (ADMIN)
    void hienThiMenuChuTich();
    void xuLyMenuChuTich(bool* dangXuat);
    // [2] TRƯỞNG PHÒNG
    void hienThiMenuTruongPhong();
    void xuLyMenuTruongPhong(bool* dangXuat);
    // [3] KẾ TOÁN
    void hienThiMenuKeToan();
    void xuLyMenuKeToan(bool* dangXuat);
    // [4] NHÂN VIÊN
    void hienThiMenuNhanVien();
    void xuLyMenuNhanVien(bool* dangXuat);

    // === CÁC CHỨC NĂNG (TÁI SỬ DỤNG) ===
    
    // Chức năng Hồ sơ
    void chucNang_ThemNhanVien();
    void chucNang_CapNhatNhanVien();
    void chucNang_QuanLyTrangThai();

    // Chức năng Xem
    void chucNang_XemDanhSach();
    void chucNang_TimKiemNhanVien(string maNV = ""); // <-- Sửa
    void chucNang_XemLichSuThayDoi();

    // Chức năng Tổ chức
    void chucNang_QuanLyPhongBan();
    void chucNang_QuanLyChucDanh(); 
    void chucNang_ThemChucDanh(); // Hàm con
    void chucNang_XemChucDanh(); // Hàm con

    // Chức năng Lương & Phúc lợi
    void chucNang_QuanLyPhucLoi();
    void chucNang_ChayBangLuong();
    void chucNang_QuanLyGoiPhucLoi(); // Hàm con
    void chucNang_GhiDanhPhucLoi(); // Hàm con
    void chucNang_XemGoiPhucLoi(); // Hàm con
    void chucNang_ThemGoiPhucLoi(); // Hàm con
    void chucNang_XoaGoiPhucLoi(); // Hàm con


    // Chức năng Báo cáo
    void chucNang_BaoCaoNhanSuTheoPhongBan();
    void chucNang_XuatDanhSachNhanVien();


public:
    QuanLyNhanSu();
    void khoiChay(); // <-- THAY ĐỔI
};

#endif // QUANLYNHANSU_H