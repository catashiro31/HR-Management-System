#include "../include/QuanLyNhanSu.h"
#include "../include/Helper.h"
#include "../include/NhanVien.h"
#include "../include/NVLuongCung.h"
#include "../include/NVTheoGio.h"
#include "../include/NVHoaHong.h"
#include "../include/PhongBan.h"
#include "../include/ChucDanh.h"
#include "../include/PhucLoi.h"
#include <iostream>
#include <iomanip>
#include <map> 
#include <fstream> 
using namespace std;


QuanLyNhanSu::QuanLyNhanSu() : currentUser(nullptr), dangChay(true) {}

void QuanLyNhanSu::khoiChay() {
    db.taiDuLieuTuFile();
    Helper::dungManHinh();

    while (dangChay) {
        Helper::xoaManHinh();
        if (dangNhap()) {
            hienThiMenuChinh();
        } else {
            // Người dùng chọn thoát (nhập '0' ở màn hình đăng nhập)
            dangChay = false;
        }
    }
    
    // Chỉ lưu khi thoát
    db.luuDuLieuVaoFile();
    cout << "Tạm biệt!" << endl;
}

bool QuanLyNhanSu::dangNhap() {
    cout << "=============================================\n";
    cout << "      HỆ THỐNG QUẢN LÝ NHÂN SỰ (HRM) \n";
    cout << "=============================================\n";
    cout << "Vui lòng đăng nhập (Nhập '0' để thoát)\n";
    
    string username, password;
    
    username = Helper::nhapChuoi(" - Tên đăng nhập (Email): ");
    if (username == "0") return false; 

    password = Helper::nhapChuoi(" - Mật khẩu: ");
    if (password == "0") return false;
    
    currentUser = db.xacThucNguoiDung(username, password);

    if (currentUser != nullptr) {
        cout << "\n >> Đăng nhập thành công! Vai trò: " 
             << Helper::roleToString(currentUser->getRole()) << "\n";
        Helper::dungManHinh();
        return true;
    } else {
        cout << "\n (!) Tên đăng nhập hoặc mật khẩu không đúng.\n";
        Helper::dungManHinh();
        return dangNhap(); // Thử lại
    }
}

void QuanLyNhanSu::hienThiMenuChinh() {
    bool dangXuat = false;
    while (!dangXuat) {
        if (currentUser == nullptr) {
            dangXuat = true;
            return;
        }
        
        switch (currentUser->getRole()) {
            case Role::CHU_TICH:
                hienThiMenuChuTich();
                xuLyMenuChuTich(&dangXuat);
                break;
            case Role::TRUONG_PHONG:
                hienThiMenuTruongPhong();
                xuLyMenuTruongPhong(&dangXuat);
                break;
            case Role::KE_TOAN:
                hienThiMenuKeToan();
                xuLyMenuKeToan(&dangXuat);
                break;
            case Role::NHAN_VIEN:
                hienThiMenuNhanVien();
                xuLyMenuNhanVien(&dangXuat);
                break;
            default:
                cout << " (!) Tài khoản không có vai trò.\n";
                dangXuat = true;
                break;
        }
    }
    
    currentUser = nullptr;
    Helper::xoaManHinh();
    cout << " >> Đã đăng xuất.\n";
    Helper::dungManHinh();
}

void QuanLyNhanSu::thoatChuongTrinh() {
    // Đã chuyển logic lưu file về hàm khoiChay()
    dangChay = false; // Chỉ cần set cờ
}

// =================== CÁC MENU ===================

void QuanLyNhanSu::hienThiMenuChuTich() {
    Helper::xoaManHinh();
    cout << "--- MENU CHỦ TỊCH (ADMIN) ---\n";
    cout << " [1] Thêm nhân viên mới\n";
    cout << " [2] Cập nhật thông tin nhân viên\n";
    cout << " [3] Quản lý trạng thái (Thăng chức, Hết HĐ)\n";
    cout << " [4] Quản lý Phòng ban\n";
    cout << " [5] Quản lý Chức danh\n";
    cout << " [6] Quản lý Phúc lợi\n";
    cout << " [7] Chạy Bảng lương\n";
    cout << " [8] Báo cáo & Xuất file\n";
    cout << " [9] Xem danh sách nhân viên (Full quyền)\n";
    cout << " [10] Xem lịch sử thay đổi NV\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}

void QuanLyNhanSu::xuLyMenuChuTich(bool* dangXuat) {
    int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 10);
    switch (luaChon) {
        case 1: chucNang_ThemNhanVien(); break; 
        case 2: chucNang_CapNhatNhanVien(); break;
        case 3: chucNang_QuanLyTrangThai(); break;
        case 4: chucNang_QuanLyPhongBan(); break;
        case 5: chucNang_QuanLyChucDanh(); break;
        case 6: chucNang_QuanLyPhucLoi(); break;
        case 7: chucNang_ChayBangLuong(); break;
        case 8: chucNang_BaoCaoNhanSuTheoPhongBan(); break; 
        case 9: chucNang_XemDanhSach(); break; 
        case 10: chucNang_XemLichSuThayDoi(); break; 
        case 0: *dangXuat = true; return;
    }
    Helper::dungManHinh();
}


void QuanLyNhanSu::hienThiMenuTruongPhong() {
    Helper::xoaManHinh();
    cout << "--- MENU TRƯỞNG PHÒNG ---\n";
    cout << " [1] Thêm nhân viên mới (vào phòng)\n";
    cout << " [2] Thăng chức (Thử việc -> Chính thức)\n";
    cout << " [3] Xem danh sách nhân viên (Phòng mình)\n";
    cout << " [4] Báo cáo doanh thu (Chưa làm)\n";
    cout << " [5] Gửi tin nhắn xin nghỉ (Chưa làm)\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuTruongPhong(bool* dangXuat) {
     int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 5);
    switch (luaChon) {
        // TODO: Cần cải tiến các hàm này để chỉ thao tác trên phòng ban của TRUONG_PHONG
        case 1: chucNang_ThemNhanVien(); break; 
        case 2: chucNang_QuanLyTrangThai(); break; 
        case 3: chucNang_XemDanhSach(); break; 
        case 4: cout << "Chức năng chưa triển khai.\n"; break;
        case 5: cout << "Chức năng chưa triển khai.\n"; break;
        case 0: *dangXuat = true; return;
    }
    Helper::dungManHinh();
}

void QuanLyNhanSu::hienThiMenuKeToan() {
    Helper::xoaManHinh();
    cout << "--- MENU KẾ TOÁN ---\n";
    cout << " [1] Chạy bảng lương (Tính & Cập nhật)\n";
    cout << " [2] Quản lý phúc lợi (Thêm/Xóa/Ghi danh)\n";
    cout << " [3] Xem danh sách nhân viên (Full lương)\n";
    cout << " [4] Báo cáo nhân sự (Theo phòng ban)\n";
    cout << " [5] Xuất file CSV\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuKeToan(bool* dangXuat) {
    int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 5);
    switch (luaChon) {
        case 1: chucNang_ChayBangLuong(); break;
        case 2: chucNang_QuanLyPhucLoi(); break;
        case 3: chucNang_XemDanhSach(); break; 
        case 4: chucNang_BaoCaoNhanSuTheoPhongBan(); break;
        case 5: chucNang_XuatDanhSachNhanVien(); break;
        case 0: *dangXuat = true; return;
    }
    Helper::dungManHinh();
}

void QuanLyNhanSu::hienThiMenuNhanVien() {
    Helper::xoaManHinh();
    cout << "--- MENU NHÂN VIÊN ---\n";
    cout << " [1] Xem thông tin cá nhân\n";
    cout << " [2] Xem danh sách nhân viên (Hạn chế)\n";
    cout << " [3] Chấm công (Chưa làm)\n";
    cout << " [4] Gửi tin nhắn xin nghỉ phép (Chưa làm)\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuNhanVien(bool* dangXuat) {
    int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 4);
    switch (luaChon) {
        case 1: chucNang_TimKiemNhanVien(currentUser->getMaNhanVien()); break;
        case 2: chucNang_XemDanhSach(); break; 
        case 3: cout << "Chức năng chưa triển khai.\n"; break;
        case 4: cout << "Chức năng chưa triển khai.\n"; break;
        case 0: *dangXuat = true; return;
    }
    Helper::dungManHinh();
}


// =================== TRIỂN KHAI CHỨC NĂNG ===================

void QuanLyNhanSu::chucNang_ThemNhanVien() {
    Helper::xoaManHinh();
    cout << "--- [1.1] Thêm Nhân Viên Mới ---\n";
    cout << " [1] Lương cố định, [2] Theo giờ, [3] Hoa hồng, [4] Quay lại\n";
    int loai = Helper::nhapSoNguyen(" >> Chọn loại NV: ", 1, 4);
    if (loai == 4) return;

    NhanVien* nvMoi = nullptr;
    string maNV_tam = "Chưa cấp"; 
    
    switch (loai) {
        case 1: nvMoi = new NVLuongCung(); break;
        case 2: nvMoi = new NVTheoGio(); break;
        case 3: nvMoi = new NVHoaHong(); break;
    }

    nvMoi->nhapThongTinCoBan(maNV_tam); 
    
    if (loai == 1) static_cast<NVLuongCung*>(nvMoi)->nhapThongTinRieng();
    else if (loai == 2) static_cast<NVTheoGio*>(nvMoi)->nhapThongTinRieng();
    else if (loai == 3) static_cast<NVHoaHong*>(nvMoi)->nhapThongTinRieng();

    cout << "--- Chọn Vai Trò (Phân Quyền) ---\n";
    cout << " [1] Chủ Tịch (Admin), [2] Trưởng Phòng, [3] Kế Toán, [4] Nhân Viên\n";
    int roleInt = Helper::nhapSoNguyen(" >> Chọn vai trò cho tài khoản: ", 1, 4);
    Role roleMoi = static_cast<Role>(roleInt);
    
    if (nvMoi != nullptr) {
        db.themNhanVien(nvMoi, roleMoi);
        cout << " >> ĐÃ THÊM NHÂN VIÊN VÀ TẠO TÀI KHOẢN THÀNH CÔNG.\n";
    }
}

void QuanLyNhanSu::chucNang_CapNhatNhanVien() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [2] Cập Nhật Thông Tin Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần cập nhật: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên.\n"; return;
    }
    cout << " >> Tìm thấy nhân viên: " << nv->getHoTen() << "\n";
    cout << " [1] Địa chỉ, [2] Mã phòng ban, [3] Mã chức danh, [4] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: {
            string giaTriCu = nv->getDiaChi();
            string giaTriMoi = Helper::nhapChuoi(" - Nhập địa chỉ mới: ");
            nv->setDiaChi(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật địa chỉ", giaTriCu, giaTriMoi);
            break;
        }
        case 2: {
            string giaTriCu = nv->getMaPhongBan();
            string giaTriMoi = Helper::nhapChuoi(" - Nhập mã phòng ban mới: ");
            nv->setMaPhongBan(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật phòng ban", giaTriCu, giaTriMoi);
            break;
        }
        case 3: {
            string giaTriCu = nv->getMaChucDanh();
            string giaTriMoi = Helper::nhapChuoi(" - Nhập mã chức danh mới: ");
            nv->setMaChucDanh(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật chức danh", giaTriCu, giaTriMoi);
            break;
        }
        case 4: return;
    }
    cout << " >> Đã cập nhật thông tin.\n";
}

void QuanLyNhanSu::chucNang_QuanLyTrangThai() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [3] Quản Lý Trạng Thái Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên.\n"; return;
    }
    string giaTriCu = Helper::trangThaiToString(nv->getTrangThai());
    cout << " >> Trạng thái hiện tại: " << giaTriCu << "\n";
    cout << " [1] Thử việc, [2] Chính thức, [3] Đã nghỉ\n";
    int trangThaiMoiInt = Helper::nhapSoNguyen(" >> Chọn trạng thái mới: ", 1, 3);
    TrangThaiLamViec trangThaiMoi = static_cast<TrangThaiLamViec>(trangThaiMoiInt);
    nv->setTrangThai(trangThaiMoi);
    string giaTriMoi = Helper::trangThaiToString(trangThaiMoi);
    db.themGhiNhanLichSu(maNV, "Thay đổi trạng thái", giaTriCu, giaTriMoi);
    cout << " >> Đã cập nhật trạng thái.\n";
    
    if (trangThaiMoi == TrangThaiLamViec::DA_NGHI) {
        // TODO: Vô hiệu hóa tài khoản
        cout << " (!) Đã chuyển sang 'Đã nghỉ'. Cần vô hiệu hóa tài khoản (Chức năng chưa làm).\n";
    }
}

void QuanLyNhanSu::chucNang_XemLichSuThayDoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [1.4] Xem Lịch Sử Thay Đổi Của Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần xem: ");
    const vector<LichSuThayDoi>* lichSu = db.layLichSuCuaNV(maNV);
    if (lichSu == nullptr || lichSu->empty()) {
        cout << " (Nhân viên này không có lịch sử thay đổi nào)\n"; return;
    }
    cout << "\nLịch sử thay đổi của Nhân viên: " << maNV << "\n";
    cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";
    cout << "| Ngày Thay Đổi  | Mô Tả                   | Giá Trị Cũ              | Giá Trị Mới             |\n";
    cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";
    for (const auto& ghiNhan : *lichSu) {
        cout << "| " << left << setw(14) << ghiNhan.ngayThayDoi.toString()
                  << " | " << setw(23) << ghiNhan.moTa
                  << " | " << setw(23) << ghiNhan.giaTriCu
                  << " | " << setw(23) << ghiNhan.giaTriMoi << " |\n";
    }
    cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";
}

void QuanLyNhanSu::chucNang_XemDanhSach() {
    // (Hàm này đã được cập nhật)
    Helper::xoaManHinh();
    cout << "--- Xem Danh Sách Nhân Viên ---\n";
    const auto& dsNhanVien = db.getDSNhanVien();
    if (dsNhanVien.empty()) {
        cout << " (Chưa có nhân viên nào trong hệ thống)\n";
        return;
    }
    Role vaiTroHienTai = currentUser->getRole();
    cout << "Hiển thị " << dsNhanVien.size() << " nhân viên (Với quyền: " 
         << Helper::roleToString(vaiTroHienTai) << ")\n";
    
    for (const NhanVien* nv : dsNhanVien) {
        nv->hienThiThongTin(vaiTroHienTai); 
    }
}

void QuanLyNhanSu::chucNang_TimKiemNhanVien(string maNV) {
    // (Hàm này đã được cập nhật)
    Helper::xoaManHinh();
    cout << "--- Tìm Kiếm Nhân Viên ---\n";
    if (maNV.empty()) {
        maNV = Helper::nhapChuoi(" - Nhập Mã NV cần tìm: ");
    }
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }
    cout << " >> Thông tin chi tiết: \n";
    nv->hienThiThongTin(currentUser->getRole());
}

void QuanLyNhanSu::chucNang_QuanLyPhongBan() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [2] Quản Lý Phòng Ban ---\n";
    cout << " [1] Thêm phòng ban mới, [2] Xem danh sách, [3] Cập nhật trưởng phòng, [4] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: {
            string maPB = Helper::nhapChuoi(" - Nhập mã PB (ví dụ: PB01): ");
            string tenPB = Helper::nhapChuoi(" - Nhập tên PB: ");
            db.themPhongBan(PhongBan(maPB, tenPB, "Chưa bổ nhiệm"));
            cout << " >> Đã thêm phòng ban.\n";
            break;
        }
        case 2: {
            const auto& dsPhongBan = db.getDSPhongBan();
            if (dsPhongBan.empty()) { cout << " (Chưa có phòng ban nào)\n"; break; }
            cout << "+------------+---------------------------+-----------------+\n";
            cout << "| Mã PB      | Tên Phòng Ban             | Mã Trưởng Phòng |\n";
            cout << "+------------+---------------------------+-----------------+\n";
            for (const auto& pb : dsPhongBan) { pb.hienThi(); }
            cout << "+------------+---------------------------+-----------------+\n";
            break;
        }
        case 3: {
            string maPB = Helper::nhapChuoi(" - Nhập mã PB cần cập nhật: ");
            PhongBan* pb = db.timPhongBanTheoMa(maPB);
            if (pb == nullptr) { cout << " (!) Không tìm thấy phòng ban.\n"; break; }
            string maTP = Helper::nhapChuoi(" - Nhập Mã NV trưởng phòng mới: ");
            pb->setMaTruongPhong(maTP);
            cout << " >> Đã cập nhật trưởng phòng.\n";
            break;
        }
        case 4: return;
    }
}

void QuanLyNhanSu::chucNang_QuanLyChucDanh() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [2.2] Quản Lý Chức Danh & Bậc Lương ---\n";
    cout << " [1] Thêm chức danh mới, [2] Xem danh sách, [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);
    switch (chon) {
        case 1: chucNang_ThemChucDanh(); break;
        case 2: chucNang_XemChucDanh(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_ThemChucDanh() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Thêm Chức Danh Mới ---\n";
    int soThuTu = db.getDSChucDanh().size() + 1;
    string maCD = Helper::taoMaTuDong("CD", soThuTu);
    cout << " - Mã chức danh (Tự động): " << maCD << "\n";
    string tenCD = Helper::nhapChuoi(" - Nhập tên chức danh: ");
    double luongCB = Helper::nhapSoThuc(" - Nhập lương cơ bản: ", 0.0);
    db.themChucDanh(ChucDanh(maCD, tenCD, luongCB));
    cout << " >> Đã thêm chức danh mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XemChucDanh() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Danh sách Chức Danh & Bậc Lương ---\n";
    const auto& dsChucDanh = db.getDSChucDanh();
    if (dsChucDanh.empty()) { cout << " (Chưa có chức danh nào)\n"; return; }
    cout << "+------------+---------------------------+-------------------+\n";
    cout << "| Mã CD      | Tên Chức Danh             | Lương Cơ Bản      |\n";
    cout << "+------------+---------------------------+-------------------+\n";
    for (const auto& cd : dsChucDanh) { cd.hienThi(); }
    cout << "+------------+---------------------------+-------------------+\n";
}

void QuanLyNhanSu::chucNang_QuanLyPhucLoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [3] Quản Lý Phúc Lợi ---\n";
    cout << " [1] Quản lý các gói phúc lợi (Thêm/Xóa), [2] Ghi danh cho Nhân Viên, [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);
    switch (chon) {
        case 1: chucNang_QuanLyGoiPhucLoi(); break;
        case 2: chucNang_GhiDanhPhucLoi(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_QuanLyGoiPhucLoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Quản Lý Các Gói Phúc Lợi ---\n";
    cout << " [1] Thêm gói, [2] Xóa gói, [3] Xem danh sách, [4] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: chucNang_ThemGoiPhucLoi(); break;
        case 2: chucNang_XoaGoiPhucLoi(); break;
        case 3: chucNang_XemGoiPhucLoi(); break;
        case 4: return;
    }
}

void QuanLyNhanSu::chucNang_ThemGoiPhucLoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Thêm Gói Phúc Lợi Mới ---\n";
    int soThuTu = db.getDSPhucLoi().size() + 1;
    string maPL = Helper::taoMaTuDong("PL", soThuTu);
    cout << " - Mã phúc lợi (Tự động): " << maPL << "\n";
    string tenPL = Helper::nhapChuoi(" - Nhập tên gói phúc lợi: ");
    double chiPhi = Helper::nhapSoThuc(" - Nhập chi phí hàng tháng: ", 0.0);
    db.themPhucLoi(PhucLoi(maPL, tenPL, chiPhi));
    cout << " >> Đã thêm gói phúc lợi mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XoaGoiPhucLoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Xóa Gói Phúc Lợi ---\n";
    chucNang_XemGoiPhucLoi();
    string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần xóa: ");
    if (db.timPhucLoiTheoMa(maPL) == nullptr) {
        cout << " (!) Mã phúc lợi không tồn tại.\n";
    } else {
        db.xoaPhucLoi(maPL);
        cout << " >> Đã xóa phúc lợi " << maPL << ".\n";
    }
}

void QuanLyNhanSu::chucNang_XemGoiPhucLoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Danh Sách Gói Phúc Lợi ---\n";
    const auto& dsPhucLoi = db.getDSPhucLoi();
    if (dsPhucLoi.empty()) { cout << " (Chưa có gói phúc lợi nào)\n"; return; }
    cout << "+------------+--------------------------------+-------------------+\n";
    cout << "| Mã PL      | Tên Phúc Lợi                   | Chi Phí Hàng Tháng |\n";
    cout << "+------------+--------------------------------+-------------------+\n";
    for (const auto& pl : dsPhucLoi) { pl.hienThi(); }
    cout << "+------------+--------------------------------+-------------------+\n";
}

void QuanLyNhanSu::chucNang_GhiDanhPhucLoi() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- Ghi Danh / Hủy Ghi Danh Phúc Lợi ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần thao tác: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) { cout << " (!) Không tìm thấy nhân viên.\n"; return; }
    cout << " >> Nhân viên: " << nv->getHoTen() << "\n";
    vector<PhucLoi*> dsDaCo = db.getPhucLoiCuaNhanVien(maNV);
    if (dsDaCo.empty()) { cout << "    (Chưa đăng ký gói nào)\n"; } 
    else { for (PhucLoi* pl : dsDaCo) { cout << "    - " << pl->getMaPhucLoi() << "\n"; } }
    cout << "\n [1] Ghi danh gói mới, [2] Hủy ghi danh, [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 3);
    if (chon == 1) {
        chucNang_XemGoiPhucLoi();
        string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần GHI DANH: ");
        if (db.ghiDanhPhucLoi(maNV, maPL)) { cout << " >> Ghi danh thành công.\n"; }
    } else if (chon == 2) {
        if (dsDaCo.empty()) { cout << " (!) Không có gì để hủy.\n"; } 
        else {
            string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần HỦY: ");
            if (db.huyGhiDanhPhucLoi(maNV, maPL)) { cout << " >> Hủy ghi danh thành công.\n"; } 
            else { cout << " (!) Hủy thất bại.\n"; }
        }
    }
}

void QuanLyNhanSu::chucNang_ChayBangLuong() {
    // (Đây là code cũ của bạn, đã nâng cấp)
    Helper::xoaManHinh();
    cout << "--- [2] Tính Lương Hàng Tháng ---\n";
    for (NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) {
            double soGio = Helper::nhapSoThuc(" - Nhập số giờ làm cho NV " + nv->getMaNV() + ": ", 0.0);
            static_cast<NVTheoGio*>(nv)->setSoGioLam(soGio);
        }
        else if (nv->getLoaiNV() == LoaiNhanVien::HOA_HONG) {
            double doanhSo = Helper::nhapSoThuc(" - Nhập doanh số cho NV " + nv->getMaNV() + ": ", 0.0);
            static_cast<NVHoaHong*>(nv)->setDoanhSo(doanhSo);
        }
    }
    cout << "\n--- BẢNG LƯƠNG THÁNG (CHI TIẾT) ---\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    cout << "| Mã NV  | Họ Tên                    | Lg. Gốc (NV)    | Lg. Chức Danh   | Giảm Trừ (PL)   | LƯƠNG THỰC LĨNH |\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    double tongChiPhiLuong = 0.0;
    for (const NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getTrangThai() == TrangThaiLamViec::DA_NGHI) continue;
        double luongGocNV = nv->tinhLuong();
        double luongChucDanh = 0.0;
        ChucDanh* cd = db.timChucDanhTheoMa(nv->getMaChucDanh());
        if (cd != nullptr) { luongChucDanh = cd->getLuongCoBan(); }
        double chiPhiPhucLoi = 0.0;
        vector<PhucLoi*> dsPhucLoiNV = db.getPhucLoiCuaNhanVien(nv->getMaNV());
        for (const PhucLoi* pl : dsPhucLoiNV) { chiPhiPhucLoi += pl->getChiPhiHangThang(); }
        double luongGop = (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) ? luongGocNV : (luongGocNV + luongChucDanh);
        double luongThucLinh = luongGop - chiPhiPhucLoi;
        tongChiPhiLuong += luongThucLinh; 
        cout << "| " << left << setw(6) << nv->getMaNV()
                  << " | " << setw(25) << nv->getHoTen()
                  << " | " << right << setw(15) << Helper::formatCurrency(luongGocNV)
                  << " | " << setw(15) << Helper::formatCurrency(luongChucDanh)
                  << " | " << setw(15) << Helper::formatCurrency(chiPhiPhucLoi)
                  << " | " << setw(15) << Helper::formatCurrency(luongThucLinh) << " |\n";
    }
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    cout << "| " << left << setw(87) << "TONG CHI PHI LUONG" 
              << " | " << right << setw(15) << Helper::formatCurrency(tongChiPhiLuong) << " |\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
}

void QuanLyNhanSu::chucNang_BaoCaoNhanSuTheoPhongBan() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [4.1] Báo Cáo Nhân Sự Theo Phòng Ban ---\n";
    const auto& dsPhongBan = db.getDSPhongBan();
    const auto& dsNhanVien = db.getDSNhanVien();
    if (dsPhongBan.empty()) { cout << " (Chưa có phòng ban nào)\n"; return; }
    map<string, int> soLuongNV;
    for (const NhanVien* nv : dsNhanVien) {
        if (nv->getTrangThai()!= TrangThaiLamViec::DA_NGHI) {
            soLuongNV[nv->getMaPhongBan()]++;
        }
    }
    cout << "+------------+---------------------------+-------------+\n";
    cout << "| Mã PB      | Tên Phòng Ban             | Số Lượng NV |\n";
    cout << "+------------+---------------------------+-------------+\n";
    for (const PhongBan& pb : dsPhongBan) {
        cout << "| " << left << setw(10) << pb.getMaPB()
                  << " | " << setw(25) << pb.getTenPB()
                  << " | " << right << setw(11) << soLuongNV[pb.getMaPB()] << " |\n";
    }
    cout << "| " << left << setw(10) << "Chưa phân bổ"
              << " | " << setw(25) << "(Chưa có phòng ban)"
              << " | " << right << setw(11) << soLuongNV[""] << " |\n";
    cout << "+------------+---------------------------+-------------+\n";
}

void QuanLyNhanSu::chucNang_XuatDanhSachNhanVien() {
    // (Đây là code cũ của bạn)
    Helper::xoaManHinh();
    cout << "--- [4.2] Xuất Danh Sách Nhân Viên (CSV) ---\n";
    string tenFile = Helper::nhapChuoi(" - Nhập tên file để xuất (ví dụ: export.csv): ");
    ofstream file(tenFile); // Lưu ở thư mục chạy
    if (!file.is_open()) { cout << " (!) Không thể tạo file.\n"; return; }
    file << "MaNV,HoTen,NgaySinh,DiaChi,MaPhongBan,MaChucDanh,TrangThai,LoaiNV\n";
    for (const NhanVien* nv : db.getDSNhanVien()) {
        file << nv->getMaNV() << ","
             << nv->getHoTen() << ","
             // << nv->getNgaySinh().toString() << "," // Cần thêm getNgaySinh() vào Nguoi.h
             << "\"" << nv->getDiaChi() << "\","
             << nv->getMaPhongBan() << ","
             << nv->getMaChucDanh() << ","
             << Helper::trangThaiToString(nv->getTrangThai()) << ","
             << static_cast<int>(nv->getLoaiNV()) << "\n";
    }
    file.close();
    cout << " >> Đã xuất thành công ra file: " << tenFile << "\n";
}