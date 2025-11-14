#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "Database.h"
#include <map>

class QuanLyNhanSu {
private:
    Database db;
    bool dangChay;

    // Hiển thị Menu
    void hienThiMenuChinh();
    void hienThiMenuHoSo();
    void hienThiMenuToChuc();
    void hienThiMenuBangLuong();
    void hienThiMenuBaoCao();

    // Xử lý Menu (Cấp 1)
    void xuLyMenuHoSo();
    void xuLyMenuToChuc();
    void xuLyMenuBangLuong();
    void xuLyMenuBaoCao();
    void thoatChuongTrinh();

    // Chức năng [1]
    void chucNang_ThemNhanVien();
    void chucNang_CapNhatNhanVien();
    void chucNang_QuanLyTrangThai();
    void chucNang_XemLichSuThayDoi();
    void chucNang_XemDanhSach();
    void chucNang_TimKiemNhanVien();

    // Chức năng [2]
    void chucNang_QuanLyPhongBan();
    void chucNang_QuanLyChucDanh(); // Hàm này ta sẽ làm

    // Chức năng [3]
    void chucNang_QuanLyPhucLoi();  // Hàm này ta sẽ làm
    void chucNang_ChayBangLuong();

    // Chức năng [4]
    void chucNang_BaoCaoNhanSuTheoPhongBan();
    void chucNang_XuatDanhSachNhanVien(); // Hàm này ta sẽ làm

    // Hàm nghiệp vụ cho [2] & [3] (Hàm con)
    void chucNang_ThemChucDanh();
    void chucNang_XemChucDanh();
    void chucNang_QuanLyGoiPhucLoi();
    void chucNang_GhiDanhPhucLoi();
    void chucNang_XemGoiPhucLoi();
    void chucNang_ThemGoiPhucLoi();
    void chucNang_XoaGoiPhucLoi();


public:
    QuanLyNhanSu();
    void chay();
};

#endif // QUANLYNHANSU_H