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
#include <vector>
#include <algorithm>

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
        
        if (currentUser->getRole() == Role::TRUONG_PHONG) {
            NhanVien* nv = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
            if (nv != nullptr) {
                cout << " >> Bạn đang quản lý Phòng: " << nv->getMaPhongBan() << "\n";
            }
        }
        
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
    cout << " [3] Quản lý trạng thái & Vai trò\n"; 
    cout << " [4] Quản lý Phòng ban\n";
    cout << " [5] Quản lý Chức danh\n";
    cout << " [6] Quản lý Phúc lợi (Thưởng)\n"; 
    cout << " [7] Chạy Bảng lương\n";
    cout << " [8] Báo cáo & Xuất file\n";
    cout << " [9] Xem danh sách nhân viên (Bảng)\n"; 
    cout << " [10] Xem DS Sắp Xếp (Lương/Chức vụ)\n"; 
    cout << " [11] Xem chi tiết nhân viên (Dọc)\n"; 
    cout << " [12] Xem lịch sử thay đổi NV\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}

void QuanLyNhanSu::xuLyMenuChuTich(bool* dangXuat) {
    Helper helper; 
    int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 12);
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
        case 10: chucNang_XemDanhSach_Sort(); break; 
        case 11: chucNang_TimKiemNhanVien(); break; 
        case 12: chucNang_XemLichSuThayDoi(); break; 
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}


void QuanLyNhanSu::hienThiMenuTruongPhong() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- MENU TRƯỞNG PHÒNG ---\n";
    cout << " [1] Thêm nhân viên mới (vào phòng)\n";
    cout << " [2] Quản lý trạng thái NV (Thử việc/Nghỉ)\n";
    cout << " [3] Xem danh sách nhân viên (Phòng mình)\n";
    cout << " [4] Xem DS Sắp Xếp (Phòng mình)\n"; 
    cout << " [5] Gửi tin nhắn xin nghỉ (Chưa làm)\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuTruongPhong(bool* dangXuat) {
    Helper helper; 
     int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 5);
    switch (luaChon) {
        case 1: chucNang_ThemNhanVien(); break; 
        case 2: chucNang_QuanLyTrangThai(); break; 
        case 3: chucNang_XemDanhSach(); break; 
        case 4: chucNang_XemDanhSach_Sort(); break; 
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
    cout << " [4] Xem DS Sắp Xếp (Lương/Chức vụ)\n"; 
    cout << " [5] Báo cáo nhân sự (Theo phòng ban)\n";
    cout << " [6] Xuất file CSV\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuKeToan(bool* dangXuat) {
    Helper helper; 
    int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 6);
    switch (luaChon) {
        case 1: chucNang_ChayBangLuong(); break;
        case 2: chucNang_QuanLyPhucLoi(); break;
        case 3: chucNang_XemDanhSach(); break; 
        case 4: chucNang_XemDanhSach_Sort(); break; 
        case 5: chucNang_BaoCaoNhanSuTheoPhongBan(); break;
        case 6: chucNang_XuatDanhSachNhanVien(); break;
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

// --- HÀM NÀY ĐÃ ĐƯỢC CẬP NHẬT (FIX LOGIC TRƯỞNG PHÒNG) ---
void QuanLyNhanSu::chucNang_ThemNhanVien() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- [1.1] Thêm Nhân Viên Mới ---\n";
    
    bool laChuTich = (currentUser->getRole() == Role::CHU_TICH);
    string maPB_CuaTruongPhong = "";
    
    if (!laChuTich) { // Nếu là Trưởng phòng
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong == nullptr) {
            cout << " (!) Lỗi: Không tìm thấy hồ sơ của bạn.\n";
            return;
        }
        maPB_CuaTruongPhong = nvTruongPhong->getMaPhongBan();
        cout << " >> (Bạn có thể thêm nhân viên mới (chỉ vai trò Nhân Viên) vào phòng " << maPB_CuaTruongPhong << ")\n";
    }

    // --- SỬA LỖI: Luôn hiển thị cả 3 loại ---
    cout << " [1] Lương cố định\n";
    cout << " [2] Theo giờ\n";
    cout << " [3] Hoa hồng\n";
    cout << " [4] Quay lại\n";
    
    int loai = helper.nhapSoNguyen(" >> Chọn loại NV: ", 1, 4);
    if (loai == 4) return;
    
    // (Đã xóa khối if-block cấm Trưởng phòng chọn 2 hoặc 3)

    Role roleMoi = Role::NHAN_VIEN; 
    bool yeuCauPhongBan = true;

    // Chỉ Chủ tịch mới được chọn vai trò, và chỉ khi tạo NV Lương Cố Định
    if (loai == 1 && laChuTich) { 
        cout << "--- Chọn Vai Trò (Phân Quyền) ---\n";
        cout << " [2] Trưởng Phòng\n";
        cout << " [3] Kế Toán\n";
        cout << " [4] Nhân Viên\n";
        int roleInt = helper.nhapSoNguyen(" >> Chọn vai trò cho tài khoản: ", 2, 4); 
        roleMoi = static_cast<Role>(roleInt); 
    } 

    if (roleMoi == Role::KE_TOAN) {
        Account* keToanCu = db.timTaiKhoanDauTienTheoVaiTro(Role::KE_TOAN);
        if (keToanCu != nullptr) {
            NhanVien* nvKeToanCu = db.timNhanVienTheoMa(keToanCu->getMaNhanVien());
            cout << " (!) Cảnh báo: Đã có Kế toán (ID: " << keToanCu->getMaNhanVien() << ").\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn giáng chức Kế toán cũ (Y/N)? ");
            if (xacNhan == "Y" || xacNhan == "y") {
                if (nvKeToanCu != nullptr) {
                    db.capNhatVaiTro(nvKeToanCu, keToanCu, Role::NHAN_VIEN);
                    cout << " >> Đã giáng chức Kế toán cũ.\n";
                    yeuCauPhongBan = false; 
                } else {
                    cout << " (!) Lỗi: Không tìm thấy hồ sơ NV của Kế toán cũ. Hủy thao tác.\n";
                    return;
                }
            } else {
                cout << " (Thao tác thêm nhân viên đã bị hủy.)\n";
                return; 
            }
        } else {
            cout << " (Vai trò: Kế Toán. Sẽ không yêu cầu nhập phòng ban.)\n";
            yeuCauPhongBan = false; 
        }
    }
    
    NhanVien* nvMoi = nullptr;
    string maNV_tam = "Chưa cấp"; 
    switch (loai) {
        case 1: nvMoi = new NVLuongCung(); break;
        case 2: nvMoi = new NVTheoGio(); break;
        case 3: nvMoi = new NVHoaHong(); break;
    }

    nvMoi->nhapThongTinCoBan(maNV_tam, yeuCauPhongBan);
    
    if (!laChuTich) {
        nvMoi->setMaPhongBan(maPB_CuaTruongPhong);
        cout << " >> Tự động gán Mã Phòng Ban: " << maPB_CuaTruongPhong << "\n";
    }
    
    string maPB = nvMoi->getMaPhongBan();
    if (yeuCauPhongBan && db.timPhongBanTheoMa(maPB) == nullptr) {
        cout << " (!) Phòng ban '" << maPB << "' không tồn tại.\n";
        string tenPB = helper.nhapChuoi(" - Nhập tên cho phòng ban mới này: ");
        db.themPhongBan(PhongBan(maPB, tenPB, "Chưa bổ nhiệm"));
        cout << " >> Đã tạo phòng ban mới: " << tenPB << "\n";
    }

    if (laChuTich && roleMoi == Role::TRUONG_PHONG) {
        PhongBan* pb = db.timPhongBanTheoMa(maPB);
        if (pb != nullptr && pb->getMaTruongPhong() != "" && pb->getMaTruongPhong() != "Chưa bổ nhiệm") {
            string maTPCu = pb->getMaTruongPhong();
            NhanVien* nvCu = db.timNhanVienTheoMa(maTPCu);
            Account* accCu = db.timTaiKhoanTheoMaNV(maTPCu);
            string tenTPCu = (nvCu != nullptr) ? nvCu->getHoTen() : maTPCu;

            cout << " (!) Cảnh báo: Phòng " << maPB << " đã có Trưởng phòng là: " << tenTPCu << ".\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn thay thế và giáng chức TP cũ (Y/N)? ");
            
            if (xacNhan == "Y" || xacNhan == "y") {
                if (nvCu != nullptr && accCu != nullptr) {
                    db.capNhatVaiTro(nvCu, accCu, Role::NHAN_VIEN);
                    cout << " >> Đã giáng chức " << tenTPCu << " xuống Nhân Viên.\n";
                } else {
                    cout << " (!) Không tìm thấy thông tin Trưởng phòng cũ. Chỉ bổ nhiệm mới.\n";
                    pb->setMaTruongPhong("Chưa bổ nhiệm"); 
                }
            } else {
                cout << " (Thao tác thêm nhân viên đã bị hủy.)\n";
                delete nvMoi; 
                return; 
            }
        }
        nvMoi->setTrangThai(TrangThaiLamViec::CHINH_THUC);
        cout << " >> (Đã tự động chuyển trạng thái sang 'Chính thức' do vai trò.)\n";
    }

    if (roleMoi == Role::KE_TOAN) {
        nvMoi->setTrangThai(TrangThaiLamViec::CHINH_THUC);
        cout << " >> (Đã tự động chuyển trạng thái sang 'Chính thức' do vai trò.)\n";
    }

    if (loai == 1) static_cast<NVLuongCung*>(nvMoi)->nhapThongTinRieng();
    else if (loai == 2) static_cast<NVTheoGio*>(nvMoi)->nhapThongTinRieng();
    else if (loai == 3) static_cast<NVHoaHong*>(nvMoi)->nhapThongTinRieng();

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

    if (currentUser->getRole() == Role::TRUONG_PHONG) {
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong == nullptr || nv->getMaPhongBan() != nvTruongPhong->getMaPhongBan()) {
            cout << " (!) Bạn không có quyền cập nhật nhân viên của phòng ban khác.\n";
            return;
        }
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
            if (currentUser->getRole() == Role::TRUONG_PHONG) {
                cout << " (!) Trưởng phòng không có quyền thay đổi phòng ban.\n";
                break;
            }
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
    
    string maPB_CuaTruongPhong = "";
    bool laChuTich = (currentUser->getRole() == Role::CHU_TICH);
    
    if (!laChuTich) { 
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong == nullptr || nv->getMaPhongBan() != nvTruongPhong->getMaPhongBan()) {
            cout << " (!) Bạn không có quyền quản lý nhân viên của phòng ban khác.\n";
            return;
        }
    }

    cout << " >> Nhân viên: " << nv->getHoTen() << "\n";
    cout << " Bạn muốn thay đổi gì?\n";
    cout << " [1] Trạng thái làm việc (Thử việc/Chính thức/Nghỉ)\n";
    if (laChuTich) {
        cout << " [2] Vai trò hệ thống (Thăng/Giáng chức)\n";
    }
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
    else if (chon == 2 && laChuTich) { 
        chucNang_ThayDoiVaiTro(nv); 
    }
    else if (chon == 3) {
        return;
    } else {
        cout << " (!) Lựa chọn không hợp lệ hoặc không có quyền.\n";
    }
}

void QuanLyNhanSu::chucNang_ThayDoiVaiTro(NhanVien* nv) {
    Helper helper;
    
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
    
    if (roleInt == 1) {
        cout << " (!) Không thể thăng chức lên 'Chủ Tịch'. Đặt làm 'Nhân Viên'.\n";
        roleInt = 4; 
    }

    Role vaiTroMoi = static_cast<Role>(roleInt); 

    if (vaiTroMoi == vaiTroCu) {
        cout << " (Vai trò mới giống hệt vai trò cũ. Không thay đổi.)\n";
        return;
    }

    // --- LOGIC MỚI: XỬ LÝ HOÁN ĐỔI (SWAP) ---
    // TRƯỜNG HỢP 1: Thăng chức TRƯỞNG PHÒNG -> KẾ TOÁN
    if (vaiTroCu == Role::TRUONG_PHONG && vaiTroMoi == Role::KE_TOAN) {
        cout << " (Phát hiện: Thăng chức Trưởng Phòng lên Kế Toán.)\n";
        Account* acc_KeToanCu = db.timTaiKhoanDauTienTheoVaiTro(Role::KE_TOAN);
        
        if (acc_KeToanCu != nullptr) { // Đã có Kế toán
            NhanVien* nv_KeToanCu = db.timNhanVienTheoMa(acc_KeToanCu->getMaNhanVien());
            if (nv_KeToanCu == nullptr) {
                cout << " (!) Lỗi nghiêm trọng: Tìm thấy tài khoản Kế toán nhưng không thấy hồ sơ NV.\n";
                return;
            }
            
            cout << " >> Kế toán cũ: " << nv_KeToanCu->getHoTen() << "\n";
            cout << " >> Trưởng phòng (sắp lên): " << nv->getHoTen() << " (Phòng " << nv->getMaPhongBan() << ")\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn HOÁN ĐỔI 2 vị trí này (Y/N)? ");

            if (xacNhan == "Y" || xacNhan == "y") {
                PhongBan* pb_cuaTP = db.timPhongBanTheoMa(nv->getMaPhongBan());
                if (pb_cuaTP == nullptr) {
                    cout << " (!) Lỗi: Phòng ban của Trưởng phòng không tồn tại.\n";
                    return;
                }
                
                // 1. Gỡ TP cũ (nv) khỏi phòng
                pb_cuaTP->setMaTruongPhong("Chưa bổ nhiệm");
                
                // 2. Cập nhật TP (nv) -> Kế toán
                db.capNhatVaiTro(nv, acc, Role::KE_TOAN);
                
                // 3. Cập nhật Kế toán cũ (nv_KeToanCu) -> Trưởng phòng
                db.capNhatVaiTro(nv_KeToanCu, acc_KeToanCu, Role::TRUONG_PHONG);
                
                // 4. Gán Kế toán cũ vào phòng của TP cũ
                nv_KeToanCu->setMaPhongBan(pb_cuaTP->getMaPB());
                pb_cuaTP->setMaTruongPhong(nv_KeToanCu->getMaNV());
                
                cout << " >> HOÁN ĐỔI THÀNH CÔNG.\n";
                return; // Kết thúc
            } else {
                cout << " (Thao tác bị hủy.)\n";
                return; // Hủy
            }
        } 
        // (Nếu không có Kế toán cũ, logic sẽ chạy xuống db.capNhatVaiTro ở dưới)
    }
    // --- KẾT THÚC LOGIC HOÁN ĐỔI ---

    // TRƯỜNG HỢP 2: Thăng chức BẤT KỲ AI -> KẾ TOÁN (mà không phải TP)
    if (vaiTroMoi == Role::KE_TOAN) {
        Account* keToanCu = db.timTaiKhoanDauTienTheoVaiTro(Role::KE_TOAN);
        if (keToanCu != nullptr && keToanCu != acc) {
            NhanVien* nvKeToanCu = db.timNhanVienTheoMa(keToanCu->getMaNhanVien());
            cout << " (!) Cảnh báo: Đã có Kế toán (ID: " << keToanCu->getMaNhanVien() << ").\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn giáng chức Kế toán cũ (Y/N)? ");
            if (xacNhan == "Y" || xacNhan == "y") {
                if (nvKeToanCu != nullptr) {
                    db.capNhatVaiTro(nvKeToanCu, keToanCu, Role::NHAN_VIEN);
                    cout << " >> Đã giáng chức Kế toán cũ.\n";
                } else {
                    cout << " (!) Lỗi: Không tìm thấy NV của Kế toán cũ. Hủy thao tác.\n";
                    return;
                }
            } else {
                cout << " (Thao tác bị hủy.)\n";
                return;
            }
        }
    }
    
    // TRƯỜNG HỢP 3: Thăng chức BẤT KỲ AI -> TRƯỞNG PHÒNG
    if (vaiTroMoi == Role::TRUONG_PHONG) {
        PhongBan* pb = db.timPhongBanTheoMa(nv->getMaPhongBan());
        if (pb == nullptr) {
            cout << " (!) Lỗi: NV này không có phòng ban (" << nv->getMaPhongBan() << "). Không thể làm Trưởng phòng.\n";
            return;
        }
        string maTPCu = pb->getMaTruongPhong();
        if (maTPCu != "" && maTPCu != "Chưa bổ nhiệm" && maTPCu != nv->getMaNV()) {
            NhanVien* nvCu = db.timNhanVienTheoMa(maTPCu);
            Account* accCu = db.timTaiKhoanTheoMaNV(maTPCu);
            string tenTPCu = (nvCu != nullptr) ? nvCu->getHoTen() : maTPCu;

            cout << " (!) Cảnh báo: Phòng " << pb->getMaPB() << " đã có TP là: " << tenTPCu << ".\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn thay thế và giáng chức TP cũ (Y/N)? ");
            if (xacNhan == "Y" || xacNhan == "y") {
                if (nvCu != nullptr && accCu != nullptr) {
                    db.capNhatVaiTro(nvCu, accCu, Role::NHAN_VIEN);
                    cout << " >> Đã giáng chức " << tenTPCu << " xuống Nhân Viên.\n";
                } else {
                    cout << " (!) Không tìm thấy thông tin TP cũ. Chỉ bổ nhiệm mới.\n";
                    pb->setMaTruongPhong("Chưa bổ nhiệm");
                }
            } else {
                cout << " (Thao tác bị hủy.)\n";
                return;
            }
        }
    }

    // Gọi hàm Database để xử lý logic (nếu không phải là swap)
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
    
    vector<NhanVien*> dsNhanVien = db.getDSNhanVien();
    Role vaiTroHienTai = currentUser->getRole();
    string maPB_CuaTruongPhong = "";

    if (vaiTroHienTai == Role::TRUONG_PHONG) {
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong != nullptr) {
            maPB_CuaTruongPhong = nvTruongPhong->getMaPhongBan();
            
            vector<NhanVien*> dsDaLoc;
            for (NhanVien* nv : dsNhanVien) {
                if (nv->getMaPhongBan() == maPB_CuaTruongPhong) {
                    dsDaLoc.push_back(nv);
                }
            }
            dsNhanVien = dsDaLoc; 
        }
    }
    
    if (dsNhanVien.empty()) {
        cout << " (Không có nhân viên nào trong hệ thống " 
             << (maPB_CuaTruongPhong.empty() ? "" : "thuộc phòng ban " + maPB_CuaTruongPhong) 
             << ")\n";
        return;
    }
    
    cout << "Hiển thị " << dsNhanVien.size() << " nhân viên (Với quyền: " 
         << helper.roleToString(vaiTroHienTai) << ")\n\n";

    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
    cout << "| Mã NV    | Họ Tên                    | Loại NV      | Email                          | Trạng Thái   | Mã PB    | Mã CD    |\n";
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
    
    for (const NhanVien* nv : dsNhanVien) {
        nv->hienThiThongTinBang(vaiTroHienTai); 
    }
    
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
}

void QuanLyNhanSu::chucNang_TimKiemNhanVien(string maNV) {
    Helper helper; 
    helper.xoaManHinh();
    
    bool dangXemCaNhan = false;
    NhanVien* nv = nullptr; // Khai báo nv ở ngoài

    if (maNV.empty()) {
        cout << "--- Xem Chi Tiết Nhân Viên ---\n";
        
        // --- LOGIC LOOP MỚI ---
        while (true) { 
            maNV = helper.nhapChuoi(" - Nhập Mã NV (Nhập '0' để quay lại): ");
            if (maNV == "0") return; // Thoát

            nv = db.timNhanVienTheoMa(maNV); // Gán cho nv
            if (nv != nullptr) {
                break; // Tìm thấy, thoát vòng lặp
            } else {
                cout << " (!) Không tìm thấy nhân viên với mã " << maNV << ".\n";
            }
        }
        // --- KẾT THÚC LOGIC LOOP ---
    } else {
        cout << "--- Xem Thông Tin Cá Nhân ---\n";
        dangXemCaNhan = (maNV == currentUser->getMaNhanVien());
        nv = db.timNhanVienTheoMa(maNV); // Phải gán nv
    }

    if (nv == nullptr) { 
        cout << " (!) Lỗi: Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }
    
    Role vaiTroXem = currentUser->getRole();

    // Logic kiểm tra quyền của Trưởng phòng
    if (vaiTroXem == Role::TRUONG_PHONG) {
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong == nullptr || nv->getMaPhongBan() != nvTruongPhong->getMaPhongBan()) {
            cout << " (!) Bạn không có quyền xem chi tiết nhân viên của phòng ban khác.\n";
            return;
        }
    }
    
    // Logic xem lương cá nhân
    if (vaiTroXem == Role::NHAN_VIEN && dangXemCaNhan) {
        vaiTroXem = Role::KE_TOAN; 
        cout << " (Bạn đang xem thông tin lương cá nhân của mình.)\n";
    }
    
    nv->hienThiThongTin(vaiTroXem);
}

void QuanLyNhanSu::chucNang_XemDanhSach_Sort() {
    Helper helper;
    helper.xoaManHinh();
    cout << "--- Xem Danh Sách Nhân Viên (Sắp xếp) ---\n";
    
    vector<NhanVien*> dsCopy = db.getDSNhanVien(); 
    Role vaiTroHienTai = currentUser->getRole();

    if (vaiTroHienTai == Role::TRUONG_PHONG) {
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong != nullptr) {
            string maPB_CuaTruongPhong = nvTruongPhong->getMaPhongBan();
            vector<NhanVien*> dsDaLoc;
            for (NhanVien* nv : dsCopy) {
                if (nv->getMaPhongBan() == maPB_CuaTruongPhong) {
                    dsDaLoc.push_back(nv);
                }
            }
            dsCopy = dsDaLoc; 
            cout << " (Chỉ hiển thị nhân viên phòng " << maPB_CuaTruongPhong << ")\n";
        }
    }

    if (dsCopy.empty()) {
        cout << " (Không có nhân viên nào để sắp xếp.)\n";
        return;
    }

    cout << "Bạn muốn sắp xếp theo:\n";
    cout << " [1] Lương thực lĩnh (Giảm dần)\n";
    cout << " [2] Mã chức danh (Tăng dần)\n";
    cout << " [0] Quay lại\n";
    int chon = helper.nhapSoNguyen(" >> Lựa chọn: ", 0, 2);

    if (chon == 1) {
        sort(dsCopy.begin(), dsCopy.end(), [](const NhanVien* a, const NhanVien* b) {
            return a->tinhLuong() > b->tinhLuong();
        });
        cout << " >> Đã sắp xếp theo Lương Giảm dần.\n";
    } else if (chon == 2) {
        sort(dsCopy.begin(), dsCopy.end(), [](const NhanVien* a, const NhanVien* b) {
            return a->getMaChucDanh() < b->getMaChucDanh();
        });
        cout << " >> Đã sắp xếp theo Mã Chức Danh Tăng dần (A-Z).\n";
    } else {
        return; 
    }
    
    cout << "\nHiển thị " << dsCopy.size() << " nhân viên (Với quyền: " 
         << helper.roleToString(vaiTroHienTai) << ")\n\n";

    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
    cout << "| Mã NV    | Họ Tên                    | Loại NV      | Email                          | Trạng Thái   | Mã PB    | Mã CD    |\n";
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
    
    for (const NhanVien* nv : dsCopy) {
        nv->hienThiThongTinBang(vaiTroHienTai); 
    }
    
    cout << "+----------+---------------------------+--------------+--------------------------------+--------------+----------+----------+\n";
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