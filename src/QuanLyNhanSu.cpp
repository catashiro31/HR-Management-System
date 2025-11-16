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
    Helper helper; 
    db.taiDuLieuTuFile();
    helper.dungManHinh();

    while (dangChay) {
        helper.xoaManHinh();
        if (dangNhap()) {
            hienThiMenuChinh();
        } else {
            dangChay = false;
        }
    }
    
    db.luuDuLieuVaoFile();
    cout << "Tạm biệt!" << endl;
}

bool QuanLyNhanSu::dangNhap() {
    Helper helper; 
    cout << "=============================================\n";
    cout << "      HỆ THỐNG QUẢN LÝ NHÂN SỰ (HRM) \n";
    cout << "=============================================\n";
    cout << "Vui lòng đăng nhập (Nhập '0' để thoát)\n";
    
    string username, password;
    
    username = helper.nhapChuoi(" - Tên đăng nhập (Email): ");
    if (username == "0") return false; 

    password = helper.nhapChuoi(" - Mật khẩu: ");
    if (password == "0") return false;
    
    currentUser = db.xacThucNguoiDung(username, password);

    if (currentUser != nullptr) {
        cout << "\n >> Đăng nhập thành công! Vai trò: " 
             << helper.roleToString(currentUser->getRole()) << "\n";
        helper.dungManHinh();
        return true;
    } else {
        cout << "\n (!) Tên đăng nhập hoặc mật khẩu không đúng.\n";
        helper.dungManHinh();
        return dangNhap(); 
    }
}

void QuanLyNhanSu::hienThiMenuChinh() {
    Helper helper; 
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
    helper.xoaManHinh();
    cout << " >> Đã đăng xuất.\n";
    helper.dungManHinh();
}

void QuanLyNhanSu::thoatChuongTrinh() {
    dangChay = false; 
}

// =================== CÁC MENU ===================

void QuanLyNhanSu::hienThiMenuChuTich() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- MENU CHỦ TỊCH (ADMIN) ---\n";
    cout << " [1] Thêm nhân viên mới\n";
    cout << " [2] Cập nhật thông tin nhân viên\n";
    cout << " [3] Quản lý trạng thái & Vai trò\n"; // <-- SỬA TÊN
    cout << " [4] Quản lý Phòng ban\n";
    cout << " [5] Quản lý Chức danh\n";
    cout << " [6] Quản lý Phúc lợi (Thưởng)\n"; // <-- SỬA TÊN
    cout << " [7] Chạy Bảng lương\n";
    cout << " [8] Báo cáo & Xuất file\n";
    cout << " [9] Xem danh sách nhân viên (Bảng)\n"; 
    cout << " [10] Xem chi tiết nhân viên (Dọc)\n"; 
    cout << " [11] Xem lịch sử thay đổi NV\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}

void QuanLyNhanSu::xuLyMenuChuTich(bool* dangXuat) {
    Helper helper; 
    int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 11);
    switch (luaChon) {
        case 1: chucNang_ThemNhanVien(); break; 
        case 2: chucNang_CapNhatNhanVien(); break;
        case 3: chucNang_QuanLyTrangThai(); break; // <-- GỌI HÀM ĐÃ SỬA
        case 4: chucNang_QuanLyPhongBan(); break;
        case 5: chucNang_QuanLyChucDanh(); break;
        case 6: chucNang_QuanLyPhucLoi(); break;
        case 7: chucNang_ChayBangLuong(); break;
        case 8: chucNang_BaoCaoNhanSuTheoPhongBan(); break; 
        case 9: chucNang_XemDanhSach(); break; 
        case 10: chucNang_TimKiemNhanVien(); break; // Gọi không có mã
        case 11: chucNang_XemLichSuThayDoi(); break; 
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}


void QuanLyNhanSu::hienThiMenuTruongPhong() {
    Helper helper; 
    helper.xoaManHinh();
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
    Helper helper; 
     int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 5);
    switch (luaChon) {
        // TODO: Cần cải tiến các hàm này để chỉ thao tác trên phòng ban của TRUONG_PHONG
        case 1: chucNang_ThemNhanVien(); break; 
        case 2: chucNang_QuanLyTrangThai(); break; // TODO: Cần giới hạn
        case 3: chucNang_XemDanhSach(); break; // TODO: Cần lọc
        case 4: cout << "Chức năng chưa triển khai.\n"; break;
        case 5: cout << "Chức năng chưa triển khai.\n"; break;
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}

void QuanLyNhanSu::hienThiMenuKeToan() {
    Helper helper; 
    helper.xoaManHinh();
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
    Helper helper; 
    int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 5);
    switch (luaChon) {
        case 1: chucNang_ChayBangLuong(); break;
        case 2: chucNang_QuanLyPhucLoi(); break;
        case 3: chucNang_XemDanhSach(); break; 
        case 4: chucNang_BaoCaoNhanSuTheoPhongBan(); break;
        case 5: chucNang_XuatDanhSachNhanVien(); break;
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}

void QuanLyNhanSu::hienThiMenuNhanVien() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- MENU NHÂN VIÊN ---\n";
    cout << " [1] Xem thông tin cá nhân (Chi tiết)\n";
    cout << " [2] Xem danh sách nhân viên (Bảng)\n";
    cout << " [3] Chấm công (Chưa làm)\n";
    cout << " [4] Gửi tin nhắn xin nghỉ phép (Chưa làm)\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuNhanVien(bool* dangXuat) {
    Helper helper; 
    int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 4);
    switch (luaChon) {
        case 1: chucNang_TimKiemNhanVien(currentUser->getMaNhanVien()); break;
        case 2: chucNang_XemDanhSach(); break; 
        case 3: cout << "Chức năng chưa triển khai.\n"; break;
        case 4: cout << "Chức năng chưa triển khai.\n"; break;
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}


// =================== TRIỂN KHAI CHỨC NĂNG ===================

void QuanLyNhanSu::chucNang_ThemNhanVien() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [1.1] Thêm Nhân Viên Mới ---\n";
    cout << " [1] Lương cố định, [2] Theo giờ, [3] Hoa hồng, [4] Quay lại\n";
    int loai = helper.nhapSoNguyen(" >> Chọn loại NV: ", 1, 4);
    if (loai == 4) return;

    NhanVien* nvMoi = nullptr;
    string maNV_tam = "Chưa cấp"; 
    
    switch (loai) {
        case 1: nvMoi = new NVLuongCung(); break;
        case 2: nvMoi = new NVTheoGio(); break;
        case 3: nvMoi = new NVHoaHong(); break;
    }

    // 1. Nhập thông tin (bao gồm maPhongBan)
    nvMoi->nhapThongTinCoBan(maNV_tam); 
    
    // 2. Logic tạo phòng ban tự động (Req 1b)
    string maPB = nvMoi->getMaPhongBan();
    if (db.timPhongBanTheoMa(maPB) == nullptr) {
        cout << " (!) Phòng ban '" << maPB << "' không tồn tại.\n";
        string tenPB = helper.nhapChuoi(" - Nhập tên cho phòng ban mới này: ");
        db.themPhongBan(PhongBan(maPB, tenPB, "Chưa bổ nhiệm"));
        cout << " >> Đã tạo phòng ban mới: " << tenPB << "\n";
    }

    // 3. Nhập thông tin lương
    if (loai == 1) static_cast<NVLuongCung*>(nvMoi)->nhapThongTinRieng();
    else if (loai == 2) static_cast<NVTheoGio*>(nvMoi)->nhapThongTinRieng();
    else if (loai == 3) static_cast<NVHoaHong*>(nvMoi)->nhapThongTinRieng();

    // 4. Chọn vai trò (Req 1a - Bỏ Chủ Tịch)
    cout << "--- Chọn Vai Trò (Phân Quyền) ---\n";
    cout << " [2] Trưởng Phòng, [3] Kế Toán, [4] Nhân Viên\n";
    int roleInt = helper.nhapSoNguyen(" >> Chọn vai trò cho tài khoản: ", 2, 4);
    Role roleMoi = static_cast<Role>(roleInt);
    
    // 5. Logic tự động lên chính thức (Req 2, 3)
    if (roleMoi == Role::TRUONG_PHONG || roleMoi == Role::KE_TOAN) {
        nvMoi->setTrangThai(TrangThaiLamViec::CHINH_THUC);
        cout << " >> (Đã tự động chuyển trạng thái sang 'Chính thức' do vai trò.)\n";
    }

    if (nvMoi != nullptr) {
        db.themNhanVien(nvMoi, roleMoi);
    }
}

void QuanLyNhanSu::chucNang_CapNhatNhanVien() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [2] Cập Nhật Thông Tin Nhân Viên ---\n";
    string maNV = helper.nhapChuoi(" - Nhập Mã NV cần cập nhật: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên.\n"; return;
    }
    cout << " >> Tìm thấy nhân viên: " << nv->getHoTen() << "\n";
    cout << " [1] Địa chỉ, [2] Mã phòng ban, [3] Mã chức danh, [4] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: {
            string giaTriCu = nv->getDiaChi();
            string giaTriMoi = helper.nhapChuoi(" - Nhập địa chỉ mới: ");
            nv->setDiaChi(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật địa chỉ", giaTriCu, giaTriMoi);
            break;
        }
        case 2: {
            string giaTriCu = nv->getMaPhongBan();
            string giaTriMoi = helper.nhapChuoi(" - Nhập mã phòng ban mới: ");
            nv->setMaPhongBan(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật phòng ban", giaTriCu, giaTriMoi);
            break;
        }
        case 3: {
            string giaTriCu = nv->getMaChucDanh();
            string giaTriMoi = helper.nhapChuoi(" - Nhập mã chức danh mới: ");
            nv->setMaChucDanh(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật chức danh", giaTriCu, giaTriMoi);
            break;
        }
        case 4: return;
    }
    cout << " >> Đã cập nhật thông tin.\n";
}

void QuanLyNhanSu::chucNang_QuanLyTrangThai() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [3] Quản Lý Trạng Thái & Vai Trò ---\n";
    string maNV = helper.nhapChuoi(" - Nhập Mã NV: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên.\n"; return;
    }
    
    cout << " >> Nhân viên: " << nv->getHoTen() << "\n";
    cout << " Bạn muốn thay đổi gì?\n";
    cout << " [1] Trạng thái làm việc (Thử việc/Chính thức/Nghỉ)\n";
    cout << " [2] Vai trò hệ thống (Thăng/Giáng chức)\n";
    cout << " [3] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Lựa chọn: ", 1, 3);

    if (chon == 1) {
        string giaTriCu = helper.trangThaiToString(nv->getTrangThai());
        cout << " >> Trạng thái hiện tại: " << giaTriCu << "\n";
        cout << " [1] Thử việc, [2] Chính thức, [3] Đã nghỉ\n";
        int trangThaiMoiInt = helper.nhapSoNguyen(" >> Chọn trạng thái mới: ", 1, 3);
        TrangThaiLamViec trangThaiMoi = static_cast<TrangThaiLamViec>(trangThaiMoiInt);
        nv->setTrangThai(trangThaiMoi);
        string giaTriMoi = helper.trangThaiToString(trangThaiMoi);
        db.themGhiNhanLichSu(maNV, "Thay đổi trạng thái", giaTriCu, giaTriMoi);
        cout << " >> Đã cập nhật trạng thái.\n";
        
        if (trangThaiMoi == TrangThaiLamViec::DA_NGHI) {
            cout << " (!) Đã chuyển sang 'Đã nghỉ'. Cần vô hiệu hóa tài khoản (Chức năng chưa làm).\n";
        }
    } 
    else if (chon == 2) {
        chucNang_ThayDoiVaiTro(nv); // Gọi hàm con
    }
    // else (chon == 3) -> return
}

void QuanLyNhanSu::chucNang_ThayDoiVaiTro(NhanVien* nv) {
    Helper helper;
    
    // Hàm này được gọi từ chucNang_QuanLyTrangThai,
    // nên không cần xoaManHinh hay tìm NV nữa
    
    Account* acc = db.timTaiKhoanTheoMaNV(nv->getMaNV());

    if (acc == nullptr) {
        cout << " (!) Không tìm thấy tài khoản của nhân viên này.\n";
        return;
    }

    Role vaiTroCu = acc->getRole();
    cout << " >> Vai trò hiện tại: " << helper.roleToString(vaiTroCu) << "\n";
    
    cout << " Chọn vai trò MỚI:\n";
    cout << " [2] Trưởng Phòng\n";
    cout << " [3] Kế Toán\n";
    cout << " [4] Nhân Viên\n";
    cout << " [0] Hủy\n";
    int roleInt = helper.nhapSoNguyen(" >> Vai trò mới: ", 0, 4);

    if (roleInt == 0) {
        cout << " (Thao tác đã hủy.)\n";
        return;
    }
    
    // Cấm thăng chức lên Chủ tịch
    if (roleInt == 1) {
        cout << " (!) Không thể thăng chức lên 'Chủ Tịch'. Đặt làm 'Nhân Viên'.\n";
        roleInt = 4; 
    }

    Role vaiTroMoi = static_cast<Role>(roleInt);

    if (vaiTroMoi == vaiTroCu) {
        cout << " (Vai trò mới giống hệt vai trò cũ. Không thay đổi.)\n";
        return;
    }

    // Tự động chuyển lên chính thức nếu được thăng chức
    if ( (vaiTroMoi == Role::TRUONG_PHONG || vaiTroMoi == Role::KE_TOAN) && 
         (nv->getTrangThai() == TrangThaiLamViec::THU_VIEC) ) {
        nv->setTrangThai(TrangThaiLamViec::CHINH_THUC);
        cout << " >> (Đã tự động thăng cấp lên 'Chính thức' do thay đổi vai trò.)\n";
    }

    // Gọi hàm Database để xử lý logic phức tạp
    db.capNhatVaiTro(nv, acc, vaiTroMoi);
}


void QuanLyNhanSu::chucNang_XemLichSuThayDoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [1.4] Xem Lịch Sử Thay Đổi Của Nhân Viên ---\n";
    string maNV = helper.nhapChuoi(" - Nhập Mã NV cần xem: ");
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
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Xem Danh Sách Nhân Viên ---\n";
    const auto& dsNhanVien = db.getDSNhanVien();
    
    if (dsNhanVien.empty()) {
        cout << " (Chưa có nhân viên nào trong hệ thống)\n";
        return;
    }
    
    Role vaiTroHienTai = currentUser->getRole();
    cout << "Hiển thị " << dsNhanVien.size() << " nhân viên (Với quyền: " 
         << helper.roleToString(vaiTroHienTai) << ")\n\n";

    // 1. Vẽ Header của Bảng (ĐÃ SỬA LẠI ĐỘ RỘNG)
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
    cout << "| Mã NV    | Họ Tên                    | Loại NV      | Email                          | Trạng Thái   | Mã PB    | Mã CD    |\n";
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
    
    // 2. Vẽ Body của Bảng
    for (const NhanVien* nv : dsNhanVien) {
        nv->hienThiThongTinBang(vaiTroHienTai); 
    }
    
    // 3. Vẽ Footer của Bảng (ĐÃ SỬA LẠI ĐỘ RỘNG)
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
}

void QuanLyNhanSu::chucNang_TimKiemNhanVien(string maNV) {
    Helper helper; 
    helper.xoaManHinh();
    
    if (maNV.empty()) {
        cout << "--- Xem Chi Tiết Nhân Viên ---\n";
        maNV = helper.nhapChuoi(" - Nhập Mã NV cần xem chi tiết: ");
    } else {
        cout << "--- Xem Thông Tin Cá Nhân ---\n";
    }

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }
    
    nv->hienThiThongTin(currentUser->getRole());
}

void QuanLyNhanSu::chucNang_QuanLyPhongBan() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [2] Quản Lý Phòng Ban ---\n";
    cout << " [1] Thêm phòng ban mới, [2] Xem danh sách, [3] Cập nhật trưởng phòng, [4] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: {
            string maPB = helper.nhapChuoi(" - Nhập mã PB (ví dụ: PB01): ");
            string tenPB = helper.nhapChuoi(" - Nhập tên PB: ");
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
            string maPB = helper.nhapChuoi(" - Nhập mã PB cần cập nhật: ");
            PhongBan* pb = db.timPhongBanTheoMa(maPB);
            if (pb == nullptr) { cout << " (!) Không tìm thấy phòng ban.\n"; break; }
            string maTP = helper.nhapChuoi(" - Nhập Mã NV trưởng phòng mới: ");
            pb->setMaTruongPhong(maTP);
            cout << " >> Đã cập nhật trưởng phòng.\n";
            break;
        }
        case 4: return;
    }
}

void QuanLyNhanSu::chucNang_QuanLyChucDanh() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [2.2] Quản Lý Chức Danh & Bậc Lương ---\n";
    cout << " [1] Thêm chức danh mới, [2] Xem danh sách, [3] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);
    switch (chon) {
        case 1: chucNang_ThemChucDanh(); break;
        case 2: chucNang_XemChucDanh(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_ThemChucDanh() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Thêm Chức Danh Mới ---\n";
    int soThuTu = db.getDSChucDanh().size() + 1;
    string maCD = helper.taoMaTuDong("CD", soThuTu);
    cout << " - Mã chức danh (Tự động): " << maCD << "\n";
    string tenCD = helper.nhapChuoi(" - Nhập tên chức danh: ");
    double luongCB = helper.nhapSoThuc(" - Nhập lương cơ bản: ", 0.0);
    db.themChucDanh(ChucDanh(maCD, tenCD, luongCB));
    cout << " >> Đã thêm chức danh mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XemChucDanh() {
    Helper helper; 
    helper.xoaManHinh();
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
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [3] Quản Lý Phúc Lợi (Thưởng) ---\n";
    cout << " [1] Quản lý các gói thưởng (Thêm/Xóa), [2] Ghi danh thưởng cho NV, [3] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);
    switch (chon) {
        case 1: chucNang_QuanLyGoiPhucLoi(); break;
        case 2: chucNang_GhiDanhPhucLoi(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_QuanLyGoiPhucLoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Quản Lý Các Gói Thưởng ---\n";
    cout << " [1] Thêm gói thưởng, [2] Xóa gói thưởng, [3] Xem danh sách, [4] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: chucNang_ThemGoiPhucLoi(); break;
        case 2: chucNang_XoaGoiPhucLoi(); break;
        case 3: chucNang_XemGoiPhucLoi(); break;
        case 4: return;
    }
}

void QuanLyNhanSu::chucNang_ThemGoiPhucLoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Thêm Gói Thưởng Mới ---\n";
    int soThuTu = db.getDSPhucLoi().size() + 1;
    string maPL = helper.taoMaTuDong("PL", soThuTu);
    cout << " - Mã thưởng (Tự động): " << maPL << "\n";
    string tenPL = helper.nhapChuoi(" - Nhập tên gói thưởng (VD: Thưởng Tết): ");
    double chiPhi = helper.nhapSoThuc(" - Nhập số tiền thưởng: ", 0.0);
    db.themPhucLoi(PhucLoi(maPL, tenPL, chiPhi));
    cout << " >> Đã thêm gói thưởng mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XoaGoiPhucLoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Xóa Gói Thưởng ---\n";
    chucNang_XemGoiPhucLoi();
    string maPL = helper.nhapChuoi(" - Nhập Mã Thưởng cần xóa: ");
    if (db.timPhucLoiTheoMa(maPL) == nullptr) {
        cout << " (!) Mã thưởng không tồn tại.\n";
    } else {
        db.xoaPhucLoi(maPL);
        cout << " >> Đã xóa gói thưởng " << maPL << ".\n";
    }
}

void QuanLyNhanSu::chucNang_XemGoiPhucLoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Danh Sách Gói Thưởng (Phúc Lợi) ---\n";
    const auto& dsPhucLoi = db.getDSPhucLoi();
    if (dsPhucLoi.empty()) { cout << " (Chưa có gói thưởng nào)\n"; return; }
    cout << "+------------+--------------------------------+-------------------+\n";
    cout << "| Mã PL      | Tên Thưởng                     | Số Tiền Thưởng    |\n";
    cout << "+------------+--------------------------------+-------------------+\n";
    for (const auto& pl : dsPhucLoi) { pl.hienThi(); }
    cout << "+------------+--------------------------------+-------------------+\n";
}

void QuanLyNhanSu::chucNang_GhiDanhPhucLoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Ghi Danh / Hủy Ghi Danh Thưởng ---\n";
    string maNV = helper.nhapChuoi(" - Nhập Mã NV cần thao tác: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) { cout << " (!) Không tìm thấy nhân viên.\n"; return; }
    cout << " >> Nhân viên: " << nv->getHoTen() << "\n";
    vector<PhucLoi*> dsDaCo = db.getPhucLoiCuaNhanVien(maNV);
    if (dsDaCo.empty()) { cout << "    (Chưa đăng ký gói thưởng nào)\n"; } 
    else { for (PhucLoi* pl : dsDaCo) { cout << "    - " << pl->getMaPhucLoi() << "\n"; } }
    cout << "\n [1] Ghi danh gói mới, [2] Hủy ghi danh, [3] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Lựa chọn: ", 1, 3);
    if (chon == 1) {
        chucNang_XemGoiPhucLoi();
        string maPL = helper.nhapChuoi(" - Nhập Mã Thưởng cần GHI DANH: ");
        if (db.ghiDanhPhucLoi(maNV, maPL)) { cout << " >> Ghi danh thành công.\n"; }
    } else if (chon == 2) {
        if (dsDaCo.empty()) { cout << " (!) Không có gì để hủy.\n"; } 
        else {
            string maPL = helper.nhapChuoi(" - Nhập Mã Thưởng cần HỦY: ");
            if (db.huyGhiDanhPhucLoi(maNV, maPL)) { cout << " >> Hủy ghi danh thành công.\n"; } 
            else { cout << " (!) Hủy thất bại.\n"; }
        }
    }
}

void QuanLyNhanSu::chucNang_ChayBangLuong() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [2] Tính Lương Hàng Tháng ---\n";
    for (NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) {
            double soGio = helper.nhapSoThuc(" - Nhập số giờ làm cho NV " + nv->getMaNV() + ": ", 0.0);
            static_cast<NVTheoGio*>(nv)->setSoGioLam(soGio);
        }
        else if (nv->getLoaiNV() == LoaiNhanVien::HOA_HONG) {
            double doanhSo = helper.nhapSoThuc(" - Nhập doanh số cho NV " + nv->getMaNV() + ": ", 0.0);
            static_cast<NVHoaHong*>(nv)->setDoanhSo(doanhSo);
        }
    }
    
    cout << "\n--- BẢNG LƯƠNG THÁNG (CHI TIẾT) ---\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    cout << "| Mã NV  | Họ Tên                    | Lg. Gốc (NV)    | Lg. Chức Danh   | Thưởng (PL)     | LƯƠNG THỰC LĨNH |\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    
    double tongChiPhiLuong = 0.0;
    for (const NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getTrangThai() == TrangThaiLamViec::DA_NGHI) continue;
        
        double luongGocNV = nv->tinhLuong();
        double luongChucDanh = 0.0;
        ChucDanh* cd = db.timChucDanhTheoMa(nv->getMaChucDanh());
        if (cd != nullptr) { luongChucDanh = cd->getLuongCoBan(); }
        
        double tienThuongPhucLoi = 0.0;
        vector<PhucLoi*> dsPhucLoiNV = db.getPhucLoiCuaNhanVien(nv->getMaNV());
        for (const PhucLoi* pl : dsPhucLoiNV) { 
            tienThuongPhucLoi += pl->getChiPhiHangThang(); 
        }
        
        double luongGop = (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) ? luongGocNV : (luongGocNV + luongChucDanh);
        
        double luongThucLinh = luongGop + tienThuongPhucLoi;
        
        tongChiPhiLuong += luongThucLinh; 
        
        cout << "| " << left << setw(6) << nv->getMaNV()
                  << " | " << setw(25) << nv->getHoTen()
                  << " | " << right << setw(15) << helper.formatCurrency(luongGocNV)
                  << " | " << setw(15) << helper.formatCurrency(luongChucDanh)
                  << " | " << setw(15) << helper.formatCurrency(tienThuongPhucLoi)
                  << " | " << setw(15) << helper.formatCurrency(luongThucLinh) << " |\n";
    }
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    cout << "| " << left << setw(87) << "TONG CHI PHI LUONG" 
              << " | " << right << setw(15) << helper.formatCurrency(tongChiPhiLuong) << " |\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
}

void QuanLyNhanSu::chucNang_BaoCaoNhanSuTheoPhongBan() {
    Helper helper; 
    helper.xoaManHinh();
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
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [4.2] Xuất Danh Sách Nhân Viên (CSV) ---\n";
    string tenFile = helper.nhapChuoi(" - Nhập tên file để xuất (ví dụ: export.csv): ");
    ofstream file(tenFile);
    if (!file.is_open()) { cout << " (!) Không thể tạo file.\n"; return; }
    file << "MaNV,HoTen,NgaySinh,DiaChi,MaPhongBan,MaChucDanh,TrangThai,LoaiNV\n";
    for (const NhanVien* nv : db.getDSNhanVien()) {
        file << nv->getMaNV() << ","
             << nv->getHoTen() << ","
             << nv->getNgaySinh().toString() << ","
             << "\"" << nv->getDiaChi() << "\","
             << nv->getMaPhongBan() << ","
             << nv->getMaChucDanh() << ","
             << helper.trangThaiToString(nv->getTrangThai()) << ","
             << static_cast<int>(nv->getLoaiNV()) << "\n";
    }
    file.close();
    cout << " >> Đã xuất thành công ra file: " << tenFile << "\n";
}