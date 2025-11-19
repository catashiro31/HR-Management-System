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
    helper.xoaManHinh();
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
        if (currentUser == nullptr) { dangXuat = true; return; }
        
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
    cout << " [6] Quản lý Phúc lợi\n"; 
    cout << " [7] Chạy Bảng lương\n";
    cout << " [8] Báo cáo nhân sự\n";
    cout << " [9] Xem danh sách nhân viên\n";
    cout << " [10] Xem danh sách sắp xếp\n";
    cout << " [11] Xem chi tiết nhân viên\n"; 
    cout << " [12] Xem lịch sử thay đổi NV\n";
    cout << " [13] Xem danh sách Tài khoản\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}

void QuanLyNhanSu::xuLyMenuChuTich(bool* dangXuat) {
    Helper helper; 
    int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 13);
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
        case 13: chucNang_XemDanhSachTaiKhoan(); break;
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}

void QuanLyNhanSu::hienThiMenuTruongPhong() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- MENU TRƯỞNG PHÒNG ---\n";
    cout << " [1] Thêm nhân viên mới\n";
    cout << " [2] Quản lý trạng thái nhân viên\n";
    cout << " [3] Xem danh sách nhân viên\n";
    cout << " [4] Xem danh sách sắp xếp\n"; 
    cout << " [5] Gửi tin nhắn xin nghỉ (tính năng chưa ra mắt)\n";
    cout << " [6] Xem danh sách tài khoản theo phòng\n";
    cout << " -------------------------------------------\n";
    cout << " [0] Đăng xuất\n";
    cout << "=============================================\n";
}
void QuanLyNhanSu::xuLyMenuTruongPhong(bool* dangXuat) {
    Helper helper; 
     int luaChon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 0, 6);
    switch (luaChon) {
        case 1: chucNang_ThemNhanVien(); break; 
        case 2: chucNang_QuanLyTrangThai(); break; 
        case 3: chucNang_XemDanhSach(); break; 
        case 4: chucNang_XemDanhSach_Sort(); break; 
        case 5: cout << "Chức năng chưa triển khai.\n"; break;
        case 6: chucNang_XemDanhSachTaiKhoan(); break;
        case 0: *dangXuat = true; return;
    }
    helper.dungManHinh();
}

void QuanLyNhanSu::hienThiMenuKeToan() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- MENU KẾ TOÁN ---\n";
    cout << " [1] Chạy bảng lương\n";
    cout << " [2] Quản lý phúc lợi\n";
    cout << " [3] Xem danh sách nhân viên\n";
    cout << " [4] Xem danh sách sắp xếp\n"; 
    cout << " [5] Báo cáo nhân sự theo phòng ban\n";
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
    cout << " [1] Xem thông tin cá nhân\n";
    cout << " [2] Xem danh sách nhân viên\n";
    cout << " [3] Chấm công\n";
    cout << " [4] Gửi tin nhắn xin nghỉ phép\n";
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
    cout << "--- Thêm Nhân Viên Mới ---\n";
    
    bool laChuTich = (currentUser->getRole() == Role::CHU_TICH);
    string maPB_CuaTruongPhong = "";
    
    if (!laChuTich) { 
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong == nullptr) {
            cout << " (!) Lỗi: Không tìm thấy hồ sơ của bạn.\n";
            return;
        }
        maPB_CuaTruongPhong = nvTruongPhong->getMaPhongBan();
        cout << " >> (Bạn có thể thêm nhân viên mới (chỉ vai trò Nhân Viên) vào phòng " << maPB_CuaTruongPhong << ")\n";
    }

    cout << " [1] Lương cố định\n";
    cout << " [2] Theo giờ\n";
    cout << " [3] Hoa hồng\n";
    cout << " [4] Nhập từ file CSV (Mới)\n";
    cout << " [5] Quay lại\n";
    
    int loai = helper.nhapSoNguyen(" >> Chọn phương thức [1-5]: ", 1, 5);
    if (loai == 5) return;

    if (loai == 4) {
        cout << "--- Hướng dẫn cấu trúc file CSV ---\n";
        cout << "Format: Loai(1/2/3),Ten,CCCD,DiaChi,SDT,NgaySinh,MaPB,MaCD,Luong1,Luong2,Luong3\n";
        string path = helper.nhapChuoi(" - Nhập tên/đường dẫn file (VD: data.csv): ");
        db.importNhanVienTuFile(path);
        helper.dungManHinh();
        return;
    }
    
    Role roleMoi = Role::NHAN_VIEN; 
    bool yeuCauPhongBan = true;

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

    // Logic tự động chuyển sang lương cứng nếu là sếp (Trưởng phòng/Kế toán)
    if ((roleMoi == Role::TRUONG_PHONG || roleMoi == Role::KE_TOAN) && loai != 1) {
        db.themNhanVien(nvMoi, roleMoi);
        NhanVien* nvTrongDB = db.timNhanVienTheoMa(nvMoi->getMaNV());
        if (nvTrongDB != nullptr) {
            chuyenDoiSangLuongCung(nvTrongDB);
            // Nếu là Trưởng phòng, cập nhật lại mã TP cho phòng ban sau khi chuyển đổi
            if (roleMoi == Role::TRUONG_PHONG) {
                PhongBan* pb = db.timPhongBanTheoMa(maPB);
                if(pb) pb->setMaTruongPhong(nvTrongDB->getMaNV());
            }
        }
        return;
    }

    if (nvMoi != nullptr) {
        db.themNhanVien(nvMoi, roleMoi);
        // Cập nhật mã TP nếu cần
        if (roleMoi == Role::TRUONG_PHONG) {
             PhongBan* pb = db.timPhongBanTheoMa(maPB);
             if(pb) pb->setMaTruongPhong(nvMoi->getMaNV());
        }
    }
}

void QuanLyNhanSu::chucNang_CapNhatNhanVien() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Cập Nhật Thông Tin Nhân Viên ---\n";
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

void QuanLyNhanSu::chuyenDoiSangLuongCung(NhanVien*& nv) {
    Helper helper;
    if (nv->getLoaiNV() == LoaiNhanVien::LUONG_CUNG) return;

    cout << "\n [!] THÔNG BÁO: Nhân viên này đang là loại '" 
         << (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO ? "Theo Giờ" : "Hoa Hồng") 
         << "'.\n";
    cout << "     Do được lên CHÍNH THỨC (hoặc làm Quản lý), cần chuyển sang chế độ LƯƠNG CỐ ĐỊNH.\n";
    
    double luongMoi = helper.nhapSoThuc(" - Nhập mức lương cơ bản mới (VND): ", 0);
    Date dateUtil; 

    NVLuongCung* nvMoi = new NVLuongCung(
        nv->getMaNV(), nv->getHoTen(), nv->getCCCD(), nv->getDiaChi(), 
        nv->getSoDienThoai(), nv->getEmail(), nv->getNgaySinh(), 
        dateUtil.layNgayHienTai(), 
        TrangThaiLamViec::CHINH_THUC, 
        nv->getMaPhongBan(), nv->getMaChucDanh(), 
        luongMoi
    );

    db.thayTheNhanVien(nvMoi);
    nv = nvMoi;
    cout << " >> Đã chuyển đổi loại nhân viên thành công.\n";
}

void QuanLyNhanSu::chucNang_QuanLyTrangThai() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Quản Lý Trạng Thái & Vai Trò ---\n";
    string maNV = helper.nhapChuoi(" - Nhập Mã NV: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên.\n"; return;
    }
    
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
        
        if (trangThaiMoi == TrangThaiLamViec::CHINH_THUC && nv->getTrangThai() != TrangThaiLamViec::CHINH_THUC) {
            chuyenDoiSangLuongCung(nv); 
        }
        
        nv->setTrangThai(trangThaiMoi);
        string giaTriMoi = helper.trangThaiToString(trangThaiMoi);
        db.themGhiNhanLichSu(maNV, "Thay đổi trạng thái", giaTriCu, giaTriMoi);
        cout << " >> Đã cập nhật trạng thái.\n";
        
        if (trangThaiMoi == TrangThaiLamViec::DA_NGHI) {
            cout << " [!] Nhân viên đã chuyển sang trạng thái 'Đã Nghỉ'.\n";
            cout << "     Đang tiến hành xóa thông tin truy cập...\n";
            db.xoaTaiKhoan(maNV);
            nv->setEmail(""); 
            cout << " >> Đã xóa tài khoản và Email.\n";
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

    if (roleInt == 0) { cout << " (Thao tác đã hủy.)\n"; return; }
    if (roleInt == 1) { roleInt = 4; } 

    Role vaiTroMoi = static_cast<Role>(roleInt); 

    if (vaiTroMoi == vaiTroCu) {
        cout << " (Vai trò mới giống hệt vai trò cũ. Không thay đổi.)\n";
        return;
    }

    if (vaiTroMoi == Role::KE_TOAN) {
        Account* keToanCu = db.timTaiKhoanDauTienTheoVaiTro(Role::KE_TOAN);
        if (keToanCu != nullptr && keToanCu != acc) {
            NhanVien* nvKeToanCu = db.timNhanVienTheoMa(keToanCu->getMaNhanVien());
            cout << " (!) Cảnh báo: Đã có Kế toán (ID: " << keToanCu->getMaNhanVien() << ").\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn HOÁN ĐỔI vị trí với Kế toán cũ (Y/N)? ");
            if (xacNhan == "Y" || xacNhan == "y") {
                if (nvKeToanCu != nullptr) {
                    db.capNhatVaiTro(nvKeToanCu, keToanCu, Role::NHAN_VIEN);
                    cout << " >> Đã giáng chức Kế toán cũ.\n";
                } else return;
            } else return;
        }
        nv->setMaPhongBan("KETOAN");
    }
    
    if (vaiTroMoi == Role::TRUONG_PHONG) {
        PhongBan* pb = db.timPhongBanTheoMa(nv->getMaPhongBan());
        if (pb == nullptr) { cout << " (!) Lỗi: NV này không có phòng ban.\n"; return; }
        string maTPCu = pb->getMaTruongPhong();
        if (maTPCu != "" && maTPCu != "Chưa bổ nhiệm" && maTPCu != nv->getMaNV()) {
            NhanVien* nvCu = db.timNhanVienTheoMa(maTPCu);
            Account* accCu = db.timTaiKhoanTheoMaNV(maTPCu);
            string tenTPCu = (nvCu != nullptr) ? nvCu->getHoTen() : maTPCu;
            cout << " (!) Cảnh báo: Phòng " << pb->getMaPB() << " đã có TP là: " << tenTPCu << ".\n";
            string xacNhan = helper.nhapChuoi(" - Bạn có muốn HOÁN ĐỔI vị trí với TP cũ (Y/N)? ");
            if (xacNhan == "Y" || xacNhan == "y") {
                if (nvCu != nullptr && accCu != nullptr) {
                    db.capNhatVaiTro(nvCu, accCu, Role::NHAN_VIEN);
                    cout << " >> Đã giáng chức " << tenTPCu << " xuống Nhân Viên.\n";
                } else {
                    pb->setMaTruongPhong("Chưa bổ nhiệm");
                }
            } else return;
        }
    }

    if ( (vaiTroMoi == Role::TRUONG_PHONG || vaiTroMoi == Role::KE_TOAN) && 
         (nv->getTrangThai() == TrangThaiLamViec::THU_VIEC) ) {
        chuyenDoiSangLuongCung(nv); 
        nv->setTrangThai(TrangThaiLamViec::CHINH_THUC);
        cout << " >> (Đã tự động thăng cấp lên 'Chính thức' do thay đổi vai trò.)\n";
    }

    db.capNhatVaiTro(nv, acc, vaiTroMoi);
}


void QuanLyNhanSu::chucNang_XemLichSuThayDoi() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Xem Lịch Sử Thay Đổi Của Nhân Viên ---\n";
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
        cout << "| " << left << setw(14) << helper.removeVietnameseAccent(ghiNhan.ngayThayDoi.toString())
                  << " | " << setw(23) << helper.removeVietnameseAccent(ghiNhan.moTa)
                  << " | " << setw(25) << helper.removeVietnameseAccent(ghiNhan.giaTriCu)
                  << " | " << setw(23) << helper.removeVietnameseAccent(ghiNhan.giaTriMoi) << " |\n";
    }
    cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";
    // helper.dungManHinh();
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
        cout << " (Không có nhân viên nào trong hệ thống)\n";
        return;
    }
    
    cout << "Hiển thị " << dsNhanVien.size() << " nhân viên (Với quyền: " 
         << helper.roleToString(vaiTroHienTai) << ")\n\n";

    string keNgang = "+------------+--------------------------------+-----------------+------------------------------------------+-----------------+------------+------------+";
    
    cout << keNgang << "\n";
    cout << "| " << left << setw(10) << "Ma NV" 
         << " | " << setw(30) << "Ho Ten" 
         << " | " << setw(15) << "Loai NV"
         << " | " << setw(40) << "Email"
         << " | " << setw(15) << "Trang Thai"
         << " | " << setw(10) << "Ma PB"
         << " | " << setw(10) << "Ma CD" << " |\n";
    cout << keNgang << "\n";
    
    for (const NhanVien* nv : dsNhanVien) {
        nv->hienThiThongTinBang(vaiTroHienTai); 
    }
    
    cout << keNgang << "\n";
    // helper.dungManHinh();
}

void QuanLyNhanSu::chucNang_XemDanhSachTaiKhoan() {
    Helper helper;
    helper.xoaManHinh();
    cout << "--- Danh Sách Tài Khoản Hệ Thống ---\n";

    const vector<Account*>& dsAcc = db.getDSTaiKhoan();
    Role myRole = currentUser->getRole();
    string myPB = "";

    if (myRole == Role::TRUONG_PHONG) {
        NhanVien* me = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (me) myPB = me->getMaPhongBan();
    }

    string keNgang = "+------------------------------------------+----------------------+----------------------+------------+";
    cout << keNgang << "\n";
    cout << "| " << left << setw(40) << "Ten Dang Nhap (Email)" 
         << " | " << setw(20) << "Mat Khau" 
         << " | " << setw(20) << "Vai Tro" 
         << " | " << setw(10) << "Ma NV" << " |\n";
    cout << keNgang << "\n";

    for (const Account* acc : dsAcc) {
        bool hienThi = false;

        if (myRole == Role::CHU_TICH) {
            hienThi = true; 
        } 
        else if (myRole == Role::TRUONG_PHONG) {
            NhanVien* nv = db.timNhanVienTheoMa(acc->getMaNhanVien());
            if (nv && nv->getMaPhongBan() == myPB) {
                hienThi = true;
            }
        }

        if (hienThi) {
            cout << "| " << left << setw(40) << helper.removeVietnameseAccent(acc->getUsername())
                 << " | " << setw(20) << helper.removeVietnameseAccent(acc->getPassword())
                 << " | " << setw(20) << helper.removeVietnameseAccent(helper.roleToString(acc->getRole()))
                 << " | " << setw(10) << helper.removeVietnameseAccent(acc->getMaNhanVien()) << " |\n";
        }
    }
    cout << keNgang << "\n";
    // helper.dungManHinh();
}

void QuanLyNhanSu::chucNang_TimKiemNhanVien(string maNV) {
    Helper helper; 
    helper.xoaManHinh();
    
    bool dangXemCaNhan = false;
    NhanVien* nv = nullptr; 

    if (maNV.empty()) {
        cout << "--- Xem Chi Tiết Nhân Viên ---\n";
        while (true) { 
            maNV = helper.nhapChuoi(" - Nhập Mã NV (Nhập '0' để quay lại): ");
            if (maNV == "0") return; 

            nv = db.timNhanVienTheoMa(maNV); 
            if (nv != nullptr) break; 
            else cout << " (!) Không tìm thấy nhân viên với mã " << maNV << ".\n";
        }
    } else {
        cout << "--- Xem Thông Tin Cá Nhân ---\n";
        dangXemCaNhan = (maNV == currentUser->getMaNhanVien());
        nv = db.timNhanVienTheoMa(maNV); 
    }

    if (nv == nullptr) { 
        cout << " (!) Lỗi: Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }
    
    Role vaiTroXem = currentUser->getRole();

    if (vaiTroXem == Role::TRUONG_PHONG) {
        NhanVien* nvTruongPhong = db.timNhanVienTheoMa(currentUser->getMaNhanVien());
        if (nvTruongPhong == nullptr || nv->getMaPhongBan() != nvTruongPhong->getMaPhongBan()) {
            cout << " (!) Bạn không có quyền xem chi tiết nhân viên của phòng ban khác.\n";
            return;
        }
    }
    
    if (vaiTroXem == Role::NHAN_VIEN && dangXemCaNhan) {
        vaiTroXem = Role::KE_TOAN; 
        cout << " (Bạn đang xem thông tin lương cá nhân của mình.)\n";
    }
    
    nv->hienThiThongTin(vaiTroXem);
    // helper.dungManHinh();
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
    
    cout << "\nHiển thị " << dsCopy.size() << " nhân viên:\n\n";

    string keNgang = "+------------+--------------------------------+-----------------+------------------------------------------+-----------------+------------+------------+";
    
    cout << keNgang << "\n";
    cout << "| " << left << setw(10) << "Ma NV" 
         << " | " << setw(30) << "Ho Ten" 
         << " | " << setw(15) << "Loai NV"
         << " | " << setw(40) << "Email"
         << " | " << setw(15) << "Trang Thai"
         << " | " << setw(10) << "Ma PB"
         << " | " << setw(10) << "Ma CD" << " |\n";
    cout << keNgang << "\n";
    
    for (const NhanVien* nv : dsCopy) {
        nv->hienThiThongTinBang(vaiTroHienTai); 
    }
    
    cout << keNgang << "\n";
    // helper.dungManHinh();
}

void QuanLyNhanSu::chucNang_QuanLyPhongBan() {
    Helper helper; 
    while (true) {
        helper.xoaManHinh();
        cout << "--- Quản Lý Phòng Ban ---\n";
        cout << " [1] Thêm phòng ban mới\n";
        cout << " [2] Xem danh sách phòng ban\n";
        cout << " [3] Bổ nhiệm Trưởng phòng (Có xem DS nhân viên)\n";
        cout << " [4] Quay lại\n";
        
        int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);
        
        switch (chon) {
            case 1: {
                string maPB = helper.nhapChuoi(" - Nhập mã PB (ví dụ: PB01): ");
                string tenPB = helper.nhapChuoi(" - Nhập tên PB: ");
                db.themPhongBan(PhongBan(maPB, tenPB, "Chưa bổ nhiệm"));
                cout << " >> Đã thêm phòng ban.\n";
                helper.dungManHinh();
                break;
            }
            case 2: {
                const auto& dsPhongBan = db.getDSPhongBan();
                if (dsPhongBan.empty()) { cout << " (Chưa có phòng ban nào)\n"; }
                else {
                    string ke = "+----------+-----------------------------+-----------------+";
                    cout << ke << "\n| " << left << setw(8) << "Ma PB" << " | " << setw(27) << "Ten Phong Ban" << " | " << setw(15) << "Ma Truong Phong" << " |\n" << ke << "\n";
                    for (const auto& pb : dsPhongBan) pb.hienThi(); 
                    cout << ke << "\n";
                }
                helper.dungManHinh();
                break;
            }
            case 3: {
                string maPB = helper.nhapChuoi(" - Nhập mã PB cần bổ nhiệm Trưởng phòng: ");
                PhongBan* pb = db.timPhongBanTheoMa(maPB);
                if (pb == nullptr) { 
                    cout << " (!) Không tìm thấy phòng ban " << maPB << ".\n"; 
                    helper.dungManHinh(); break; 
                }
                
                cout << "\n--- DANH SÁCH ỨNG CỬ VIÊN (PHÒNG " << maPB << ") ---\n";
                const vector<NhanVien*>& dsNV = db.getDSNhanVien();
                string keNgang = "+------------+--------------------------------+-----------------+------------------------------------------+-----------------+------------+------------+";
                cout << keNgang << "\n| " << left << setw(10) << "Ma NV" << " | " << setw(30) << "Ho Ten" << " | " << setw(15) << "Loai NV" << " | " << setw(40) << "Email" << " | " << setw(15) << "Trang Thai" << " | " << setw(10) << "Ma PB" << " | " << setw(10) << "Ma CD" << " |\n" << keNgang << "\n";
                
                bool coNhanVien = false;
                for (const NhanVien* nv : dsNV) {
                    if (nv->getMaPhongBan() == maPB) { 
                        nv->hienThiThongTinBang(Role::CHU_TICH); 
                        coNhanVien = true;
                    }
                }
                cout << keNgang << "\n";

                if (!coNhanVien) {
                    cout << " (!) Phòng ban này hiện chưa có nhân viên nào.\n";
                    helper.dungManHinh(); break; 
                }

                while (true) {
                    string maNV = helper.nhapChuoi(" - Nhập Mã NV muốn bổ nhiệm (hoặc '0' để hủy): ");
                    if (maNV == "0") break; 

                    NhanVien* nvMoi = db.timNhanVienTheoMa(maNV);
                    Account* accMoi = db.timTaiKhoanTheoMaNV(maNV);

                    if (nvMoi == nullptr || accMoi == nullptr) {
                        cout << " (!) Không tìm thấy nhân viên hoặc tài khoản. Vui lòng nhập lại.\n";
                        continue;
                    }
                    if (nvMoi->getMaPhongBan() != maPB) {
                        cout << " (!) Nhân viên này thuộc phòng " << nvMoi->getMaPhongBan() << ", không phải " << maPB << ". Vui lòng nhập lại.\n";
                        continue;
                    }

                    db.capNhatVaiTro(nvMoi, accMoi, Role::TRUONG_PHONG);
                    break; 
                }
                helper.dungManHinh();
                break;
            }
            case 4: return;
        }
    }
}

void QuanLyNhanSu::chucNang_QuanLyChucDanh() {
    Helper helper; 
    while (true) {
        helper.xoaManHinh();
        cout << "--- Quản Lý Chức Danh & Bậc Lương ---\n";
        cout << " [1] Thêm chức danh mới\n [2] Xem danh sách\n [3] Quay lại\n";
        int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);
        switch (chon) {
            case 1: chucNang_ThemChucDanh(); helper.dungManHinh(); break;
            case 2: chucNang_XemChucDanh(); helper.dungManHinh(); break;
            case 3: return;
        }
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
    string ke = "+----------+-----------------------------+-------------------+";
    cout << ke << "\n";
    cout << "| " << left << setw(8) << "Ma CD" << " | " << setw(27) << "Ten Chuc Danh" << " | " << setw(17) << "Luong Co Ban" << " |\n";
    cout << ke << "\n";
    for (const auto& cd : dsChucDanh) { cd.hienThi(); }
    cout << ke << "\n";
}

void QuanLyNhanSu::chucNang_QuanLyPhucLoi() {
    Helper helper; 
    while (true) {
        helper.xoaManHinh();
        cout << "--- Quản Lý Thưởng ---\n";
        cout << " [1] Quản lý các gói thưởng (Thêm/Xóa)\n [2] Ghi danh thưởng cho NV\n [3] Quay lại\n";
        int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);
        switch (chon) {
            case 1: chucNang_QuanLyGoiPhucLoi(); break;
            case 2: chucNang_GhiDanhPhucLoi(); helper.dungManHinh(); break;
            case 3: return;
        }
    }
}

void QuanLyNhanSu::chucNang_QuanLyGoiPhucLoi() {
    Helper helper; 
    while (true) {
        helper.xoaManHinh();
        cout << "--- Quản Lý Các Gói Thưởng ---\n";
        cout << " [1] Thêm gói thưởng\n [2] Xóa gói thưởng\n [3] Xem danh sách\n [4] Quay lại\n";
        int chon = helper.nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);
        switch (chon) {
            case 1: chucNang_ThemGoiPhucLoi(); helper.dungManHinh(); break;
            case 2: chucNang_XoaGoiPhucLoi(); helper.dungManHinh(); break;
            case 3: chucNang_XemGoiPhucLoi(); helper.dungManHinh(); break;
            case 4: return;
        }
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
    string ke = "+------------+----------------------------------+-------------------+";
    cout << ke << "\n";
    cout << "| " << left << setw(10) << "Ma PL" << " | " << setw(32) << "Ten Thuong" << " | " << setw(17) << "So Tien Thuong" << " |\n";
    cout << ke << "\n";
    for (const auto& pl : dsPhucLoi) { pl.hienThi(); }
    cout << ke << "\n";
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
    cout << "\n [1] Ghi danh gói mới\n";
    cout << " [2] Hủy ghi danh\n";
    cout << " [3] Quay lại\n";
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
    cout << "--- Tính Lương Hàng Tháng ---\n";

    string choice = helper.nhapChuoi(" - Bạn có muốn cập nhật Giờ làm/Doanh số mới cho nhân viên không? (Y/N): ");
    
    if (choice == "Y" || choice == "y") {
        cout << "\n >> Bắt đầu nhập liệu chấm công...\n";
        for (NhanVien* nv : db.getDSNhanVien()) {
            if (nv->getTrangThai() == TrangThaiLamViec::DA_NGHI) continue;

            if (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) {
                string prompt = " - Nhập số giờ làm cho " + nv->getMaNV() + " (" + nv->getHoTen() + "): ";
                double soGio = helper.nhapSoThuc(prompt, 0.0);
                static_cast<NVTheoGio*>(nv)->setSoGioLam(soGio);
            }
            else if (nv->getLoaiNV() == LoaiNhanVien::HOA_HONG) {
                string prompt = " - Nhập doanh số cho " + nv->getMaNV() + " (" + nv->getHoTen() + "): ";
                double doanhSo = helper.nhapSoThuc(prompt, 0.0);
                static_cast<NVHoaHong*>(nv)->setDoanhSo(doanhSo);
            }
        }
        cout << " >> Đã cập nhật dữ liệu chấm công thành công.\n";
        db.luuDuLieuVaoFile(); 
    } else {
        cout << " >> Sử dụng dữ liệu chấm công hiện tại để tính lương.\n";
    }
    
    cout << "\n--- BẢNG LƯƠNG THÁNG (CHI TIẾT) ---\n";
    string ke = "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+";
    cout << ke << "\n";
    cout << "| " << left << setw(6) << "Ma NV" << " | " << setw(25) << "Ho Ten" << " | " << setw(15) << "Lg. Goc (NV)" << " | " << setw(15) << "Lg. Chuc Danh" << " | " << setw(15) << "Thuong (PL)" << " | " << setw(15) << "LUONG THUC LINH" << " |\n";
    cout << ke << "\n";
    
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
    cout << ke << "\n";
    cout << "| " << left << setw(88) << "TONG CHI PHI LUONG" 
              << " | " << right << setw(15) << helper.formatCurrency(tongChiPhiLuong) << " |\n";
    cout << ke << "\n";
    // helper.dungManHinh();
}

void QuanLyNhanSu::chucNang_BaoCaoNhanSuTheoPhongBan() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Báo Cáo Nhân Sự Theo Phòng Ban ---\n";
    const auto& dsPhongBan = db.getDSPhongBan();
    const auto& dsNhanVien = db.getDSNhanVien();
    if (dsPhongBan.empty()) { cout << " (Chưa có phòng ban nào)\n"; return; }
    map<string, int> soLuongNV;
    for (const NhanVien* nv : dsNhanVien) {
        if (nv->getTrangThai()!= TrangThaiLamViec::DA_NGHI) {
            soLuongNV[nv->getMaPhongBan()]++;
        }
    }
    string ke = "+-----------------+-----------------------------+-------------+";
    cout << ke << "\n";
    cout << "| " << left << setw(15) << "Ma PB" << " | " << setw(27) << "Ten Phong Ban" << " | " << setw(11) << "So Luong NV" << " |\n";
    cout << ke << "\n";
    for (const PhongBan& pb : dsPhongBan) {
        cout << "| " << left << setw(15) << pb.getMaPB()
                  << " | " << setw(27) << pb.getTenPB()
                  << " | " << right << setw(11) << soLuongNV[pb.getMaPB()] << " |\n";
    }
    cout << "| " << left << setw(15) << "Chua phan bo"
              << " | " << setw(27) << "(Chua co phong ban)"
              << " | " << right << setw(11) << soLuongNV[""] << " |\n";
    cout << ke << "\n";
    // helper.dungManHinh();
}

void QuanLyNhanSu::chucNang_XuatDanhSachNhanVien() {
    Helper helper; 
    helper.xoaManHinh();
    cout << "--- Xuất Danh Sách Nhân Viên (CSV) ---\n";
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
    // helper.dungManHinh();
}