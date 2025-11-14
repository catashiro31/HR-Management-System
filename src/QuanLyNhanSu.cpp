#include "../include/QuanLyNhanSu.h"
#include "../include/Helper.h"
// Các include cho NhanVien, PhongBan, ChucDanh, PhucLoi...
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


QuanLyNhanSu::QuanLyNhanSu() : dangChay(true) {
    
    cout << "Đang tải dữ liệu..." << endl;
    db.taiDuLieuTuFile();
    Helper::dungManHinh();
}

void QuanLyNhanSu::chay() {
    while (dangChay) {
        hienThiMenuChinh();
        int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn của bạn: ", 0, 5);
        
        switch (luaChon) {
            case 1: xuLyMenuHoSo(); break;
            case 2: xuLyMenuToChuc(); break;
            case 3: xuLyMenuBangLuong(); break;
            case 4: xuLyMenuBaoCao(); break;
            case 0: thoatChuongTrinh(); break;
            default:
                cout << " (!) Lựa chọn không hợp lệ.\n";
                Helper::dungManHinh();
                break;
        }
    }
}

// =================== HIỂN THỊ MENU ===================

void QuanLyNhanSu::hienThiMenuChinh() {
    Helper::xoaManHinh();
    cout << "=============================================\n";
    cout << "      HỆ THỐNG QUẢN LÝ NHÂN SỰ (HRM) \n";
    cout << "=============================================\n";
    cout << " [1] Quản lý Hồ sơ Nhân sự\n";
    cout << " [2] Quản lý Tổ chức\n";
    cout << " [3] Bảng lương & Phúc lợi\n";
    cout << " [4] Báo cáo & Mở rộng\n"; // Sửa lại
    cout << " -------------------------------------------\n";
    cout << " [0] Lưu & Thoát\n"; // Sửa lại
    cout << "=============================================\n";
}

void QuanLyNhanSu::hienThiMenuHoSo() {
    // (Giữ nguyên hàm này của bạn)
    Helper::xoaManHinh();
    cout << "--- [1] QUẢN LÝ HỒ SƠ NHÂN SỰ ---\n";
    cout << " [1] Thêm nhân viên mới\n";
    cout << " [2] Cập nhật thông tin nhân viên\n";
    cout << " [3] Quản lý trạng thái\n";
    cout << " [4] Xem lịch sử thay đổi của nhân viên\n";
    cout << " [5] Xem danh sách (Tóm tắt)\n"; // Sửa lại
    cout << " [6] Xem chi tiết / Tìm kiếm NV\n"; // Sửa lại
    cout << " --------------------------------\n";
    cout << " [7] Trở về Menu Chính\n";
    cout << "----------------------------------\n";
}

void QuanLyNhanSu::hienThiMenuToChuc() {
    Helper::xoaManHinh();
    cout << "--- [2] QUẢN LÝ TỔ CHỨC ---\n";
    cout << " [1] Quản lý Phòng ban\n";
    cout << " [2] Quản lý Chức danh & Bậc lương\n"; // <-- ĐÃ CÓ THỂ SỬ DỤNG
    cout << " ----------------------------------\n";
    cout << " [3] Trở về Menu Chính\n";
    cout << "----------------------------------\n";
}

void QuanLyNhanSu::hienThiMenuBangLuong() {
    Helper::xoaManHinh();
    cout << "--- [3] BẢNG LƯƠNG & PHÚC LỢI ---\n";
    cout << " [1] Quản lý Phúc lợi\n"; // <-- ĐÃ CÓ THỂ SỬ DỤNG
    cout << " [2] Quy trình Xử lý Lương\n";
    cout << " ----------------------------------\n";
    cout << " [3] Trở về Menu Chính\n";
}

void QuanLyNhanSu::hienThiMenuBaoCao() {
    Helper::xoaManHinh();
    cout << "--- [4] BÁO CÁO & MỞ RỘNG ---\n"; // Đổi tên
    cout << " [1] Báo cáo nhân sự theo phòng ban\n";
    cout << " [2] Xuất danh sách nhân viên (CSV)\n"; // <-- Sắp làm
    cout << " ----------------------------------\n";
    cout << " [3] Trở về Menu Chính\n";
}


// =================== XỬ LÝ NGHIỆP VỤ ===================

// [1] XỬ LÝ MENU HỒ SƠ
void QuanLyNhanSu::xuLyMenuHoSo() {
    bool troVe = false;
    while (!troVe) {
        hienThiMenuHoSo();
        int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn (1 -> 7): ", 1, 7);
        
        switch (luaChon) {
            case 1: chucNang_ThemNhanVien(); break;
            case 2: chucNang_CapNhatNhanVien(); break;
            case 3: chucNang_QuanLyTrangThai(); break;
            case 4: chucNang_XemLichSuThayDoi(); break;
            case 5: chucNang_XemDanhSach(); break;
            case 6: chucNang_TimKiemNhanVien(); break;
            case 7: troVe = true; break;
            default: cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

//... (chucNang_ThemNhanVien không đổi)...
void QuanLyNhanSu::chucNang_ThemNhanVien() {
    Helper::xoaManHinh();
    cout << "--- [1.1] Thêm Nhân Viên Mới ---\n";
    cout << " Chọn loại nhân viên:\n";
    cout << " [1] Nhân viên hưởng lương cố định (Salaried)\n";
    cout << " [2] Nhân viên hưởng lương theo giờ (Hourly)\n";
    cout << " [3] Nhân viên hưởng lương theo hoa hồng (Commission)\n";
    cout << " [4] Quay lại\n";
    int loai = Helper::nhapSoNguyen(" >> Chọn loại NV: ", 1, 4);

    if (loai == 4) return;

    NhanVien* nvMoi = nullptr;
    string maNV_tam = "Chưa cấp"; 
    
    switch (loai) {
        case 1: {
            NVLuongCung* nv = new NVLuongCung();
            nv->nhapThongTinCoBan(maNV_tam); 
            nv->nhapThongTinRieng(); 
            nvMoi = nv;
            break;
        }
        case 2: {
            NVTheoGio* nv = new NVTheoGio();
            nv->nhapThongTinCoBan(maNV_tam); 
            nv->nhapThongTinRieng(); 
            nvMoi = nv;
            break;
        }
        case 3: {
            NVHoaHong* nv = new NVHoaHong();
            nv->nhapThongTinCoBan(maNV_tam); 
            nv->nhapThongTinRieng(); 
            nvMoi = nv;
            break;
        }
    }

    if (nvMoi!= nullptr) {
        db.themNhanVien(nvMoi);
        cout << " >> ĐÃ THÊM NHÂN VIÊN THÀNH CÔNG.\n";
    }
}


// CẬP NHẬT HÀM NÀY ĐỂ GHI LẠI LỊCH SỬ
void QuanLyNhanSu::chucNang_CapNhatNhanVien() {
    Helper::xoaManHinh();
    cout << "--- [2] Cập Nhật Thông Tin Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần cập nhật: ");

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }

    cout << " >> Tìm thấy nhân viên: " << nv->getHoTen() << "\n";
    cout << " Bạn muốn cập nhật gì?\n";
    cout << " [1] Địa chỉ\n";
    cout << " [2] Mã phòng ban\n";
    cout << " [3] Mã chức danh\n";
    cout << " [4] Quay lại\n";

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
        case 4:
            return;
    }
    cout << " >> Đã cập nhật thông tin.\n";
}

// CẬP NHẬT HÀM NÀY ĐỂ GHI LẠI LỊCH SỬ
void QuanLyNhanSu::chucNang_QuanLyTrangThai() {
    Helper::xoaManHinh();
    cout << "--- [3] Quản Lý Trạng Thái Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần thay đổi trạng thái: ");

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }

    cout << " >> Tìm thấy: " << nv->getHoTen() << "\n";
    string giaTriCu = Helper::trangThaiToString(nv->getTrangThai());
    cout << " >> Trạng thái hiện tại: " << giaTriCu << "\n";

    cout << " Chọn trạng thái mới:\n";
    cout << " [1] Thử việc\n";
    cout << " [2] Chính thức\n";
    cout << " [3] Đã nghỉ\n";
    int trangThaiMoiInt = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 3);

    TrangThaiLamViec trangThaiMoi = static_cast<TrangThaiLamViec>(trangThaiMoiInt);
    nv->setTrangThai(trangThaiMoi);
    string giaTriMoi = Helper::trangThaiToString(trangThaiMoi);

    db.themGhiNhanLichSu(maNV, "Thay đổi trạng thái", giaTriCu, giaTriMoi);
    cout << " >> Đã cập nhật trạng thái thành công.\n";
}

// HÀM MỚI
void QuanLyNhanSu::chucNang_XemLichSuThayDoi() {
    Helper::xoaManHinh();
    cout << "--- [1.4] Xem Lịch Sử Thay Đổi Của Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần xem: ");

    const vector<LichSuThayDoi>* lichSu = db.layLichSuCuaNV(maNV);

    if (lichSu == nullptr || lichSu->empty()) {
        cout << " (Nhân viên này không có lịch sử thay đổi nào)\n";
        return;
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


void QuanLyNhanSu::chucNang_TimKiemNhanVien() {
    Helper::xoaManHinh();
    cout << "--- [2] Tìm Kiếm Nhân Viên ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần tìm: ");

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }

    cout << " >> Tìm thấy nhân viên: \n";
    nv->hienThiThongTin();
}

void QuanLyNhanSu::chucNang_XemDanhSach() {
    Helper::xoaManHinh();
    cout << "--- [1.5] Xem Danh Sách Nhân Viên ---\n";
    const auto& dsNhanVien = db.getDSNhanVien();

    if (dsNhanVien.empty()) {
        cout << " (Chưa có nhân viên nào trong hệ thống)\n";
        return;
    }

    cout << "Hiển thị tất cả " << dsNhanVien.size() << " nhân viên:\n";
    cout << "------------------------------------------\n";
    for (const NhanVien* nv : dsNhanVien) {
        nv->hienThiThongTin();
    }
}

// [2] XỬ LÝ MENU TỔ CHỨC
void QuanLyNhanSu::xuLyMenuToChuc() {
    // (Giữ nguyên hàm này của bạn)
    bool troVe = false;
    while (!troVe) {
        hienThiMenuToChuc();
        int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn (2.1 -> 2.3): ", 1, 3);
        
        switch (luaChon) {
            case 1: chucNang_QuanLyPhongBan(); break;
            case 2: chucNang_QuanLyChucDanh(); break; // <-- HÀM MỚI
            case 3: troVe = true; break;
            default: cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

// (Hàm chucNang_QuanLyPhongBan của bạn giữ nguyên)
void QuanLyNhanSu::chucNang_QuanLyPhongBan() {
    Helper::xoaManHinh();
    cout << "--- [2] Quản Lý Phòng Ban ---\n";
    cout << " [1] Thêm phòng ban mới\n";
    cout << " [2] Xem danh sách phòng ban\n";
    cout << " [3] Cập nhật trưởng phòng\n";
    cout << " [4] Quay lại\n";
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
            if (dsPhongBan.empty()) {
                cout << " (Chưa có phòng ban nào)\n";
                break;
            }
            cout << "+------------+---------------------------+-----------------+\n";
            cout << "| Mã PB      | Tên Phòng Ban             | Mã Trưởng Phòng |\n";
            cout << "+------------+---------------------------+-----------------+\n";
            for (const auto& pb : dsPhongBan) {
                pb.hienThi();
            }
            cout << "+------------+---------------------------+-----------------+\n";
            break;
        }
        case 3: {
            string maPB = Helper::nhapChuoi(" - Nhập mã PB cần cập nhật: ");
            PhongBan* pb = db.timPhongBanTheoMa(maPB);
            if (pb == nullptr) {
                cout << " (!) Không tìm thấy phòng ban.\n";
                break;
            }
            string maTP = Helper::nhapChuoi(" - Nhập Mã NV trưởng phòng mới: ");
            pb->setMaTruongPhong(maTP);
            cout << " >> Đã cập nhật trưởng phòng.\n";
            break;
        }
        case 4:
            return;
    }
}

// ========================================================
// --- HÀM MỚI [2.2] QUẢN LÝ CHỨC DANH ---
void QuanLyNhanSu::chucNang_QuanLyChucDanh() {
    Helper::xoaManHinh();
    cout << "--- [2.2] Quản Lý Chức Danh & Bậc Lương ---\n";
    cout << " [1] Thêm chức danh mới\n";
    cout << " [2] Xem danh sách chức danh\n";
    cout << " [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);

    switch (chon) {
        case 1: chucNang_ThemChucDanh(); break;
        case 2: chucNang_XemChucDanh(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_ThemChucDanh() {
    Helper::xoaManHinh();
    cout << "--- Thêm Chức Danh Mới ---\n";
    
    // Tự động tạo mã
    int soThuTu = db.getDSChucDanh().size() + 1;
    string maCD = Helper::taoMaTuDong("CD", soThuTu);
    cout << " - Mã chức danh (Tự động): " << maCD << "\n";

    string tenCD = Helper::nhapChuoi(" - Nhập tên chức danh: ");
    double luongCB = Helper::nhapSoThuc(" - Nhập lương cơ bản: ", 0.0);

    db.themChucDanh(ChucDanh(maCD, tenCD, luongCB));
    cout << " >> Đã thêm chức danh mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XemChucDanh() {
    Helper::xoaManHinh();
    cout << "--- Danh sách Chức Danh & Bậc Lương ---\n";
    const auto& dsChucDanh = db.getDSChucDanh();

    if (dsChucDanh.empty()) {
        cout << " (Chưa có chức danh nào)\n";
        return;
    }

    cout << "+------------+---------------------------+-------------------+\n";
    cout << "| Mã CD      | Tên Chức Danh             | Lương Cơ Bản      |\n";
    cout << "+------------+---------------------------+-------------------+\n";
    for (const auto& cd : dsChucDanh) {
        cd.hienThi();
    }
    cout << "+------------+---------------------------+-------------------+\n";
}
// ========================================================



// [3] XỬ LÝ MENU BẢNG LƯƠNG
void QuanLyNhanSu::xuLyMenuBangLuong() {
    // (Giữ nguyên hàm này của bạn)
    bool troVe = false;
    while (!troVe) {
        hienThiMenuBangLuong();
        int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn (4.1 -> 4.3): ", 1, 3);
        
        switch (luaChon) {
            case 1: chucNang_QuanLyPhucLoi(); break; // <-- HÀM MỚI
            case 2: chucNang_ChayBangLuong(); break;
            case 3: troVe = true; break;
            default: cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

// ========================================================
// --- HÀM MỚI [3.1] QUẢN LÝ PHÚC LỢI ---
void QuanLyNhanSu::chucNang_QuanLyPhucLoi() {
    Helper::xoaManHinh();
    cout << "--- [3] Quản Lý Phúc Lợi ---\n";
    cout << " [1] Quản lý các gói phúc lợi (Thêm/Xóa)\n";
    cout << " [2] Ghi danh / ủy ghi danh cho Nhân Viên\n";
    cout << " [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);

    switch (chon) {
        case 1: chucNang_QuanLyGoiPhucLoi(); break;
        case 2: chucNang_GhiDanhPhucLoi(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_QuanLyGoiPhucLoi() {
    Helper::xoaManHinh();
    cout << "--- Quản Lý Các Gói Phúc Lợi ---\n";
    cout << " [1] Thêm gói phúc lợi mới\n";
    cout << " [2] Xóa gói phúc lợi\n";
    cout << " [3] Xem danh sách gói phúc lợi\n";
    cout << " [4] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);

    switch (chon) {
        case 1: chucNang_ThemGoiPhucLoi(); break;
        case 2: chucNang_XoaGoiPhucLoi(); break;
        case 3: chucNang_XemGoiPhucLoi(); break;
        case 4: return;
    }
}

void QuanLyNhanSu::chucNang_ThemGoiPhucLoi() {
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
    Helper::xoaManHinh();
    cout << "--- Xóa Gói Phúc Lợi ---\n";
    chucNang_XemGoiPhucLoi(); // Hiển thị danh sách
    string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần xóa: ");

    if (db.timPhucLoiTheoMa(maPL) == nullptr) {
        cout << " (!) Mã phúc lợi không tồn tại.\n";
    } else {
        db.xoaPhucLoi(maPL);
        cout << " >> Đã xóa phúc lợi " << maPL << " và hủy đăng ký khỏi tất cả NV.\n";
    }
}

void QuanLyNhanSu::chucNang_XemGoiPhucLoi() {
    Helper::xoaManHinh();
    cout << "--- Danh Sách Gói Phúc Lợi ---\n";
    const auto& dsPhucLoi = db.getDSPhucLoi();
    if (dsPhucLoi.empty()) {
        cout << " (Chưa có gói phúc lợi nào)\n";
        return;
    }
    cout << "+------------+--------------------------------+-------------------+\n";
    cout << "| Mã PL      | Tên Phúc Lợi                   | Chi Phí Hàng Tháng |\n";
    cout << "+------------+--------------------------------+-------------------+\n";
    for (const auto& pl : dsPhucLoi) {
        pl.hienThi();
    }
    cout << "+------------+--------------------------------+-------------------+\n";
}

void QuanLyNhanSu::chucNang_GhiDanhPhucLoi() {
    Helper::xoaManHinh();
    cout << "--- Ghi Danh / Hủy Ghi Danh Phúc Lợi ---\n";
    string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần thao tác: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        cout << " (!) Không tìm thấy nhân viên.\n";
        return;
    }

    cout << " >> Nhân viên: " << nv->getHoTen() << "\n";
    cout << " >> Các gói phúc lợi hiện tại:\n";
    vector<PhucLoi*> dsDaCo = db.getPhucLoiCuaNhanVien(maNV);
    if (dsDaCo.empty()) {
        cout << "    (Chưa đăng ký gói nào)\n";
    } else {
        for (PhucLoi* pl : dsDaCo) {
            cout << "    - " << pl->getMaPhucLoi() << ": " << pl->getTenPhucLoi() << "\n";
        }
    }

    cout << "\n [1] Ghi danh gói mới\n";
    cout << " [2] ủy ghi danh gói đã có\n";
    cout << " [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 3);

    if (chon == 1) {
        chucNang_XemGoiPhucLoi(); // Hiện DS để chọn
        string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần GHI DANH: ");
        if (db.ghiDanhPhucLoi(maNV, maPL)) {
            cout << " >> Ghi danh thành công.\n";
        }
    } else if (chon == 2) {
        if (dsDaCo.empty()) {
            cout << " (!) Nhân viên không có gì để hủy.\n";
        } else {
            string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần HỦY: ");
            if (db.huyGhiDanhPhucLoi(maNV, maPL)) {
                cout << " >> Hủy ghi danh thành công.\n";
            } else {
                cout << " (!) Hủy thất bại (Mã PL sai hoặc NV chưa đăng ký).\n";
            }
        }
    }
}
// ========================================================

// Hàm này nằm trong file QuanLyNhanSu.cpp
void QuanLyNhanSu::chucNang_ChayBangLuong() {
    Helper::xoaManHinh();
    cout << "--- [2] Tính Lương Hàng Tháng ---\n"; // Giữ theo code của bạn
    cout << " (Chức năng này sẽ tính toán lương cho tất cả nhân viên)\n";

    // --- Phần 1: Nhập liệu (Giữ nguyên code của bạn) ---
    for (NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) {
            NVTheoGio* nvTheoGio = static_cast<NVTheoGio*>(nv);
            double soGio = Helper::nhapSoThuc(" - Nhập số giờ làm cho NV " + nv->getMaNV() + " (" + nv->getHoTen() + "): ", 0.0);
            nvTheoGio->setSoGioLam(soGio);
        }
        else if (nv->getLoaiNV() == LoaiNhanVien::HOA_HONG) {
            NVHoaHong* nvHoaHong = static_cast<NVHoaHong*>(nv);
            double doanhSo = Helper::nhapSoThuc(" - Nhập doanh số cho NV " + nv->getMaNV() + " (" + nv->getHoTen() + "): ", 0.0);
            nvHoaHong->setDoanhSo(doanhSo);
        }
    }

    // --- Phần 2: Tính toán và In Bảng Lương (Đã nâng cấp để trừ Phúc Lợi) ---
    cout << "\n--- BẢNG LƯƠNG THÁNG (CHI TIẾT) ---\n";
    // Mở rộng bảng để thêm cột "Giảm Trừ (PL)"
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    cout << "| Mã NV  | Họ Tên                    | Lg. Gốc (NV)    | Lg. Chức Danh   | Giảm Trừ (PL)   | LƯƠNG THỰC LĨNH |\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    
    double tongChiPhiLuong = 0.0;

    for (const NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getTrangThai() == TrangThaiLamViec::DA_NGHI) continue;
        
        // 1. Lấy lương gốc từ chính Nhân viên (tinhLuong() ảo)
        double luongGocNV = nv->tinhLuong();

        // 2. Lấy lương từ Chức Danh (từ Database)
        double luongChucDanh = 0.0;
        ChucDanh* cd = db.timChucDanhTheoMa(nv->getMaChucDanh());
        if (cd != nullptr) {
            luongChucDanh = cd->getLuongCoBan();
        }

        // 3. (MỚI) Tính tổng chi phí phúc lợi đã đăng ký
        double chiPhiPhucLoi = 0.0;
        vector<PhucLoi*> dsPhucLoiNV = db.getPhucLoiCuaNhanVien(nv->getMaNV());
        for (const PhucLoi* pl : dsPhucLoiNV) {
            chiPhiPhucLoi += pl->getChiPhiHangThang();
        }

        // 4. Tính lương tổng (Lương Gộp)
        double luongGop = 0.0;
        if (nv->getLoaiNV() == LoaiNhanVien::THEO_GIO) {
            luongGop = luongGocNV; // Lương NV Theo Giờ đã là tổng
            luongChucDanh = 0.0; // Không áp dụng lương chức danh
        } else {
            // NV Lương Cứng và Hoa Hồng
            luongGop = luongGocNV + luongChucDanh;
        }
        
        // 5. (MỚI) Tính Lương Thực Lĩnh = Lương Gộp - Chi Phí Phúc Lợi
        double luongThucLinh = luongGop - chiPhiPhucLoi;
        
        tongChiPhiLuong += luongThucLinh; // Cộng vào tổng

        // 6. In ra
        cout << "| " << left << setw(6) << nv->getMaNV()
                  << " | " << setw(25) << nv->getHoTen()
                  << " | " << right << setw(15) << Helper::formatCurrency(luongGocNV)
                  << " | " << setw(15) << Helper::formatCurrency(luongChucDanh)
                  << " | " << setw(15) << Helper::formatCurrency(chiPhiPhucLoi) // In cột mới
                  << " | " << setw(15) << Helper::formatCurrency(luongThucLinh) << " |\n";
    }
    
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
    // Cập nhật lại setw cho dòng tổng (tăng thêm 18 ký tự cho cột mới)
    cout << "| " << left << setw(87) // (69 + 18)
              << "TONG CHI PHI LUONG" 
              << " | " << right << setw(15) << Helper::formatCurrency(tongChiPhiLuong) << " |\n";
    cout << "+--------+---------------------------+-----------------+-----------------+-----------------+-----------------+\n";
}


// [4] XỬ LÝ MENU BÁO CÁO
void QuanLyNhanSu::xuLyMenuBaoCao() {
    // (Hàm này của bạn)
    bool troVe = false;
    while (!troVe) {
        hienThiMenuBaoCao();
        int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn (4.1 -> 4.3): ", 1, 3);

        switch (luaChon) {
            case 1: chucNang_BaoCaoNhanSuTheoPhongBan(); break;
            case 2: chucNang_XuatDanhSachNhanVien(); break; // <-- HÀM MỚI
            case 3: troVe = true; break;
            default: cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

void QuanLyNhanSu::chucNang_BaoCaoNhanSuTheoPhongBan() {
    Helper::xoaManHinh();
    cout << "--- [4.1] Báo Cáo Nhân Sự Theo Phòng Ban ---\n";

    const auto& dsPhongBan = db.getDSPhongBan();
    const auto& dsNhanVien = db.getDSNhanVien();

    if (dsPhongBan.empty()) {
        cout << " (Chưa có phòng ban nào)\n";
        return;
    }

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
              << " | " << setw(25) << "(Nhân viên chưa có phòng ban)"
              << " | " << right << setw(11) << soLuongNV[""] << " |\n";

    cout << "+------------+---------------------------+-------------+\n";
}


// ========================================================
// --- HÀM MỚI [4.2] XUẤT FILE CSV ---
void QuanLyNhanSu::chucNang_XuatDanhSachNhanVien() {
    Helper::xoaManHinh();
    cout << "--- [4.2] Xuất Danh Sách Nhân Viên (CSV) ---\n";
    string tenFile = Helper::nhapChuoi(" - Nhập tên file để xuất (ví dụ: export.csv): ");
    tenFile = "../Stored/" + tenFile; // Lưu trong thư mục Stored
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << " (!) Không thể tạo file để xuất.\n";
        return;
    }

    // Ghi tiêu đề
    file << "MaNV,HoTen,NgaySinh,DiaChi,MaPhongBan,MaChucDanh,TrangThai,LoaiNV\n";

    // Ghi dữ liệu
    for (const NhanVien* nv : db.getDSNhanVien()) {
        file << nv->getMaNV() << ","
             << nv->getHoTen() << ","
             << "\"" << nv->getDiaChi() << "\"," // Thêm "" để xử lý dấu phẩy trong địa chỉ
             << nv->getMaPhongBan() << ","
             << nv->getMaChucDanh() << ","
             << Helper::trangThaiToString(nv->getTrangThai()) << ","
             << static_cast<int>(nv->getLoaiNV()) << "\n";
    }

    file.close();
    cout << " >> Đã xuất thành công danh sách " << db.getDSNhanVien().size()
              << " Nhân viên ra file: " << tenFile << "\n";
}
// ========================================================


void QuanLyNhanSu::thoatChuongTrinh() {
    cout << "Bạn có chắc chắn muốn lưu và thoát?\n";
    cout << "[1] Đồng ý\n";
    cout << "[2] Hủy\n";
    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 2);
    if (chon == 1) {
        db.luuDuLieuVaoFile();
        cout << "Tạm biệt!" << endl;
        dangChay = false;
    }
}