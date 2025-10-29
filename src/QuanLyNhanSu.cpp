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
// Include thư viện
#include <iostream>
#include <iomanip>
#include <map> // Cần cho báo cáo
#include <fstream> // Cần cho xuất file

QuanLyNhanSu::QuanLyNhanSu() : dangChay(true) {
    // TẢI DỮ LIỆU KHI KHỞI TẠO
    std::cout << "Đang tải dữ liệu..." << std::endl;
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
                std::cout << " (!) Lựa chọn không hợp lệ.\n";
                Helper::dungManHinh();
                break;
        }
    }
}

// =================== HIỂN THỊ MENU ===================

void QuanLyNhanSu::hienThiMenuChinh() {
    Helper::xoaManHinh();
    std::cout << "=============================================\n";
    std::cout << "      HỆ THỐNG QUẢN LÝ NHÂN SỰ (HRM) \n";
    std::cout << "=============================================\n";
    std::cout << " [1] Quản lý Hồ sơ Nhân sự\n";
    std::cout << " [2] Quản lý Tổ chức\n";
    std::cout << " [3] Bảng lương & Phúc lợi\n";
    std::cout << " [4] Báo cáo & Mở rộng\n"; // Sửa lại
    std::cout << " -------------------------------------------\n";
    std::cout << " [0] Lưu & Thoát\n"; // Sửa lại
    std::cout << "=============================================\n";
}

void QuanLyNhanSu::hienThiMenuHoSo() {
    // (Giữ nguyên hàm này của bạn)
    Helper::xoaManHinh();
    std::cout << "--- [1] QUẢN LÝ HỒ SƠ NHÂN SỰ ---\n";
    std::cout << " [1.1] Thêm nhân viên mới\n";
    std::cout << " [1.2] Cập nhật thông tin nhân viên\n";
    std::cout << " [1.3] Quản lý trạng thái\n";
    std::cout << " [1.4] Xem lịch sử thay đổi của nhân viên\n";
    std::cout << " [1.5] Xem danh sách (Tóm tắt)\n"; // Sửa lại
    std::cout << " [1.6] Xem chi tiết / Tìm kiếm NV\n"; // Sửa lại
    std::cout << " --------------------------------\n";
    std::cout << " [1.7] Trở về Menu Chính\n";
    std::cout << "----------------------------------\n";
}

void QuanLyNhanSu::hienThiMenuToChuc() {
    Helper::xoaManHinh();
    std::cout << "--- [2] QUẢN LÝ TỔ CHỨC ---\n";
    std::cout << " [2.1] Quản lý Phòng ban\n";
    std::cout << " [2.2] Quản lý Chức danh & Bậc lương\n"; // <-- ĐÃ CÓ THỂ SỬ DỤNG
    std::cout << " ----------------------------------\n";
    std::cout << " [2.3] Trở về Menu Chính\n";
    std::cout << "----------------------------------\n";
}

void QuanLyNhanSu::hienThiMenuBangLuong() {
    Helper::xoaManHinh();
    std::cout << "--- [3] BẢNG LƯƠNG & PHÚC LỢI ---\n";
    std::cout << " [3.1] Quản lý Phúc lợi\n"; // <-- ĐÃ CÓ THỂ SỬ DỤNG
    std::cout << " [3.2] Quy trình Xử lý Lương\n";
    std::cout << " ----------------------------------\n";
    std::cout << " [3.3] Trở về Menu Chính\n";
}

void QuanLyNhanSu::hienThiMenuBaoCao() {
    Helper::xoaManHinh();
    std::cout << "--- [4] BÁO CÁO & MỞ RỘNG ---\n"; // Đổi tên
    std::cout << " [4.1] Báo cáo nhân sự theo phòng ban\n";
    std::cout << " [4.2] Xuất danh sách nhân viên (CSV)\n"; // <-- Sắp làm
    std::cout << " ----------------------------------\n";
    std::cout << " [4.3] Trở về Menu Chính\n";
}


// =================== XỬ LÝ NGHIỆP VỤ ===================

// [1] XỬ LÝ MENU HỒ SƠ
void QuanLyNhanSu::xuLyMenuHoSo() {
    bool troVe = false;
    while (!troVe) {
        hienThiMenuHoSo();
        int luaChon = Helper::nhapSoNguyen(" >> Nhập lựa chọn (1.1 -> 1.7): ", 1, 7);
        
        switch (luaChon) {
            case 1: chucNang_ThemNhanVien(); break;
            case 2: chucNang_CapNhatNhanVien(); break;
            case 3: chucNang_QuanLyTrangThai(); break;
            case 4: chucNang_XemLichSuThayDoi(); break;
            case 5: chucNang_XemDanhSach(); break;
            case 6: chucNang_TimKiemNhanVien(); break;
            case 7: troVe = true; break;
            default: std::cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

//... (chucNang_ThemNhanVien không đổi)...
void QuanLyNhanSu::chucNang_ThemNhanVien() {
    Helper::xoaManHinh();
    std::cout << "--- [1.1] Thêm Nhân Viên Mới ---\n";
    std::cout << " Chọn loại nhân viên:\n";
    std::cout << " [1] Nhân viên hưởng lương cố định (Salaried)\n";
    std::cout << " [2] Nhân viên hưởng lương theo giờ (Hourly)\n";
    std::cout << " [3] Nhân viên hưởng lương theo hoa hồng (Commission)\n";
    std::cout << " [4] Quay lại\n";
    int loai = Helper::nhapSoNguyen(" >> Chọn loại NV: ", 1, 4);

    if (loai == 4) return;

    NhanVien* nvMoi = nullptr;
    std::string maNV_tam = "Chưa cấp"; 
    
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
        std::cout << " >> ĐÃ THÊM NHÂN VIÊN THÀNH CÔNG.\n";
    }
}


// CẬP NHẬT HÀM NÀY ĐỂ GHI LẠI LỊCH SỬ
void QuanLyNhanSu::chucNang_CapNhatNhanVien() {
    Helper::xoaManHinh();
    std::cout << "--- [1.2] Cập Nhật Thông Tin Nhân Viên ---\n";
    std::string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần cập nhật: ");

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        std::cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }

    std::cout << " >> Tìm thấy nhân viên: " << nv->getHoTen() << "\n";
    std::cout << " Bạn muốn cập nhật gì?\n";
    std::cout << " [1] Địa chỉ\n";
    std::cout << " [2] Mã phòng ban\n";
    std::cout << " [3] Mã chức danh\n";
    std::cout << " [4] Quay lại\n";

    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 4);
    switch (chon) {
        case 1: {
            std::string giaTriCu = nv->getDiaChi();
            std::string giaTriMoi = Helper::nhapChuoi(" - Nhập địa chỉ mới: ");
            nv->setDiaChi(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật địa chỉ", giaTriCu, giaTriMoi);
            break;
        }
        case 2: {
            std::string giaTriCu = nv->getMaPhongBan();
            std::string giaTriMoi = Helper::nhapChuoi(" - Nhập mã phòng ban mới: ");
            nv->setMaPhongBan(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật phòng ban", giaTriCu, giaTriMoi);
            break;
        }
        case 3: {
            std::string giaTriCu = nv->getMaChucDanh();
            std::string giaTriMoi = Helper::nhapChuoi(" - Nhập mã chức danh mới: ");
            nv->setMaChucDanh(giaTriMoi);
            db.themGhiNhanLichSu(maNV, "Cập nhật chức danh", giaTriCu, giaTriMoi);
            break;
        }
        case 4:
            return;
    }
    std::cout << " >> Đã cập nhật thông tin.\n";
}

// CẬP NHẬT HÀM NÀY ĐỂ GHI LẠI LỊCH SỬ
void QuanLyNhanSu::chucNang_QuanLyTrangThai() {
    Helper::xoaManHinh();
    std::cout << "--- [1.3] Quản Lý Trạng Thái Nhân Viên ---\n";
    std::string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần thay đổi trạng thái: ");

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        std::cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }

    std::cout << " >> Tìm thấy: " << nv->getHoTen() << "\n";
    std::string giaTriCu = Helper::trangThaiToString(nv->getTrangThai());
    std::cout << " >> Trạng thái hiện tại: " << giaTriCu << "\n";

    std::cout << " Chọn trạng thái mới:\n";
    std::cout << " [1] Thử việc\n";
    std::cout << " [2] Chính thức\n";
    std::cout << " [3] Đã nghỉ\n";
    int trangThaiMoiInt = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 3);

    TrangThaiLamViec trangThaiMoi = static_cast<TrangThaiLamViec>(trangThaiMoiInt);
    nv->setTrangThai(trangThaiMoi);
    std::string giaTriMoi = Helper::trangThaiToString(trangThaiMoi);

    db.themGhiNhanLichSu(maNV, "Thay đổi trạng thái", giaTriCu, giaTriMoi);
    std::cout << " >> Đã cập nhật trạng thái thành công.\n";
}

// HÀM MỚI
void QuanLyNhanSu::chucNang_XemLichSuThayDoi() {
    Helper::xoaManHinh();
    std::cout << "--- [1.4] Xem Lịch Sử Thay Đổi Của Nhân Viên ---\n";
    std::string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần xem: ");

    const std::vector<LichSuThayDoi>* lichSu = db.layLichSuCuaNV(maNV);

    if (lichSu == nullptr || lichSu->empty()) {
        std::cout << " (Nhân viên này không có lịch sử thay đổi nào)\n";
        return;
    }

    std::cout << "\nLịch sử thay đổi của Nhân viên: " << maNV << "\n";
    std::cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";
    std::cout << "| Ngày Thay Đổi  | Mô Tả                   | Giá Trị Cũ              | Giá Trị Mới             |\n";
    std::cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";

    for (const auto& ghiNhan : *lichSu) {
        std::cout << "| " << std::left << std::setw(14) << ghiNhan.ngayThayDoi.toString()
                  << " | " << std::setw(23) << ghiNhan.moTa
                  << " | " << std::setw(23) << ghiNhan.giaTriCu
                  << " | " << std::setw(23) << ghiNhan.giaTriMoi << " |\n";
    }
    std::cout << "+----------------+-------------------------+-------------------------+-------------------------+\n";
}


void QuanLyNhanSu::chucNang_TimKiemNhanVien() {
    Helper::xoaManHinh();
    std::cout << "--- [1.2] Tìm Kiếm Nhân Viên ---\n";
    std::string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần tìm: ");

    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        std::cout << " (!) Không tìm thấy nhân viên với mã " << maNV << "\n";
        return;
    }

    std::cout << " >> Tìm thấy nhân viên: \n";
    nv->hienThiThongTin();
}

void QuanLyNhanSu::chucNang_XemDanhSach() {
    Helper::xoaManHinh();
    std::cout << "--- [1.5] Xem Danh Sách Nhân Viên ---\n";
    const auto& dsNhanVien = db.getDSNhanVien();

    if (dsNhanVien.empty()) {
        std::cout << " (Chưa có nhân viên nào trong hệ thống)\n";
        return;
    }

    std::cout << "Hiển thị tất cả " << dsNhanVien.size() << " nhân viên:\n";
    std::cout << "------------------------------------------\n";
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
            default: std::cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

// (Hàm chucNang_QuanLyPhongBan của bạn giữ nguyên)
void QuanLyNhanSu::chucNang_QuanLyPhongBan() {
    Helper::xoaManHinh();
    std::cout << "--- [2.1] Quản Lý Phòng Ban ---\n";
    std::cout << " [1] Thêm phòng ban mới\n";
    std::cout << " [2] Xem danh sách phòng ban\n";
    std::cout << " [3] Cập nhật trưởng phòng\n";
    std::cout << " [4] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 4);

    switch (chon) {
        case 1: {
            std::string maPB = Helper::nhapChuoi(" - Nhập mã PB (ví dụ: PB01): ");
            std::string tenPB = Helper::nhapChuoi(" - Nhập tên PB: ");
            db.themPhongBan(PhongBan(maPB, tenPB, "Chưa bổ nhiệm"));
            std::cout << " >> Đã thêm phòng ban.\n";
            break;
        }
        case 2: {
            const auto& dsPhongBan = db.getDSPhongBan();
            if (dsPhongBan.empty()) {
                std::cout << " (Chưa có phòng ban nào)\n";
                break;
            }
            std::cout << "+------------+---------------------------+-----------------+\n";
            std::cout << "| Mã PB      | Tên Phòng Ban             | Mã Trưởng Phòng |\n";
            std::cout << "+------------+---------------------------+-----------------+\n";
            for (const auto& pb : dsPhongBan) {
                pb.hienThi();
            }
            std::cout << "+------------+---------------------------+-----------------+\n";
            break;
        }
        case 3: {
            std::string maPB = Helper::nhapChuoi(" - Nhập mã PB cần cập nhật: ");
            PhongBan* pb = db.timPhongBanTheoMa(maPB);
            if (pb == nullptr) {
                std::cout << " (!) Không tìm thấy phòng ban.\n";
                break;
            }
            std::string maTP = Helper::nhapChuoi(" - Nhập Mã NV trưởng phòng mới: ");
            pb->setMaTruongPhong(maTP);
            std::cout << " >> Đã cập nhật trưởng phòng.\n";
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
    std::cout << "--- [2.2] Quản Lý Chức Danh & Bậc Lương ---\n";
    std::cout << " [1] Thêm chức danh mới\n";
    std::cout << " [2] Xem danh sách chức danh\n";
    std::cout << " [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);

    switch (chon) {
        case 1: chucNang_ThemChucDanh(); break;
        case 2: chucNang_XemChucDanh(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_ThemChucDanh() {
    Helper::xoaManHinh();
    std::cout << "--- Thêm Chức Danh Mới ---\n";
    
    // Tự động tạo mã
    int soThuTu = db.getDSChucDanh().size() + 1;
    std::string maCD = Helper::taoMaTuDong("CD", soThuTu);
    std::cout << " - Mã chức danh (Tự động): " << maCD << "\n";

    std::string tenCD = Helper::nhapChuoi(" - Nhập tên chức danh: ");
    double luongCB = Helper::nhapSoThuc(" - Nhập lương cơ bản: ", 0.0);

    db.themChucDanh(ChucDanh(maCD, tenCD, luongCB));
    std::cout << " >> Đã thêm chức danh mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XemChucDanh() {
    Helper::xoaManHinh();
    std::cout << "--- Danh sách Chức Danh & Bậc Lương ---\n";
    const auto& dsChucDanh = db.getDSChucDanh();

    if (dsChucDanh.empty()) {
        std::cout << " (Chưa có chức danh nào)\n";
        return;
    }

    std::cout << "+------------+---------------------------+-------------------+\n";
    std::cout << "| Mã CD      | Tên Chức Danh             | Lương Cơ Bản      |\n";
    std::cout << "+------------+---------------------------+-------------------+\n";
    for (const auto& cd : dsChucDanh) {
        cd.hienThi();
    }
    std::cout << "+------------+---------------------------+-------------------+\n";
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
            default: std::cout << " (!) Lựa chọn không hợp lệ.\n"; break;
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
    std::cout << "--- [3.1] Quản Lý Phúc Lợi ---\n";
    std::cout << " [1] Quản lý các gói phúc lợi (Thêm/Xóa)\n";
    std::cout << " [2] Ghi danh / ủy ghi danh cho Nhân Viên\n";
    std::cout << " [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Nhập lựa chọn: ", 1, 3);

    switch (chon) {
        case 1: chucNang_QuanLyGoiPhucLoi(); break;
        case 2: chucNang_GhiDanhPhucLoi(); break;
        case 3: return;
    }
}

void QuanLyNhanSu::chucNang_QuanLyGoiPhucLoi() {
    Helper::xoaManHinh();
    std::cout << "--- Quản Lý Các Gói Phúc Lợi ---\n";
    std::cout << " [1] Thêm gói phúc lợi mới\n";
    std::cout << " [2] Xóa gói phúc lợi\n";
    std::cout << " [3] Xem danh sách gói phúc lợi\n";
    std::cout << " [4] Quay lại\n";
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
    std::cout << "--- Thêm Gói Phúc Lợi Mới ---\n";
    
    int soThuTu = db.getDSPhucLoi().size() + 1;
    std::string maPL = Helper::taoMaTuDong("PL", soThuTu);
    std::cout << " - Mã phúc lợi (Tự động): " << maPL << "\n";

    std::string tenPL = Helper::nhapChuoi(" - Nhập tên gói phúc lợi: ");
    double chiPhi = Helper::nhapSoThuc(" - Nhập chi phí hàng tháng: ", 0.0);

    db.themPhucLoi(PhucLoi(maPL, tenPL, chiPhi));
    std::cout << " >> Đã thêm gói phúc lợi mới thành công.\n";
}

void QuanLyNhanSu::chucNang_XoaGoiPhucLoi() {
    Helper::xoaManHinh();
    std::cout << "--- Xóa Gói Phúc Lợi ---\n";
    chucNang_XemGoiPhucLoi(); // Hiển thị danh sách
    std::string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần xóa: ");

    if (db.timPhucLoiTheoMa(maPL) == nullptr) {
        std::cout << " (!) Mã phúc lợi không tồn tại.\n";
    } else {
        db.xoaPhucLoi(maPL);
        std::cout << " >> Đã xóa phúc lợi " << maPL << " và hủy đăng ký khỏi tất cả NV.\n";
    }
}

void QuanLyNhanSu::chucNang_XemGoiPhucLoi() {
    Helper::xoaManHinh();
    std::cout << "--- Danh Sách Gói Phúc Lợi ---\n";
    const auto& dsPhucLoi = db.getDSPhucLoi();
    if (dsPhucLoi.empty()) {
        std::cout << " (Chưa có gói phúc lợi nào)\n";
        return;
    }
    std::cout << "+------------+--------------------------------+-------------------+\n";
    std::cout << "| Mã PL      | Tên Phúc Lợi                   | Chi Phí Hàng Tháng |\n";
    std::cout << "+------------+--------------------------------+-------------------+\n";
    for (const auto& pl : dsPhucLoi) {
        pl.hienThi();
    }
    std::cout << "+------------+--------------------------------+-------------------+\n";
}

void QuanLyNhanSu::chucNang_GhiDanhPhucLoi() {
    Helper::xoaManHinh();
    std::cout << "--- Ghi Danh / Hủy Ghi Danh Phúc Lợi ---\n";
    std::string maNV = Helper::nhapChuoi(" - Nhập Mã NV cần thao tác: ");
    NhanVien* nv = db.timNhanVienTheoMa(maNV);
    if (nv == nullptr) {
        std::cout << " (!) Không tìm thấy nhân viên.\n";
        return;
    }

    std::cout << " >> Nhân viên: " << nv->getHoTen() << "\n";
    std::cout << " >> Các gói phúc lợi hiện tại:\n";
    std::vector<PhucLoi*> dsDaCo = db.getPhucLoiCuaNhanVien(maNV);
    if (dsDaCo.empty()) {
        std::cout << "    (Chưa đăng ký gói nào)\n";
    } else {
        for (PhucLoi* pl : dsDaCo) {
            std::cout << "    - " << pl->getMaPhucLoi() << ": " << pl->getTenPhucLoi() << "\n";
        }
    }

    std::cout << "\n [1] Ghi danh gói mới\n";
    std::cout << " [2] ủy ghi danh gói đã có\n";
    std::cout << " [3] Quay lại\n";
    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 3);

    if (chon == 1) {
        chucNang_XemGoiPhucLoi(); // Hiện DS để chọn
        std::string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần GHI DANH: ");
        if (db.ghiDanhPhucLoi(maNV, maPL)) {
            std::cout << " >> Ghi danh thành công.\n";
        }
    } else if (chon == 2) {
        if (dsDaCo.empty()) {
            std::cout << " (!) Nhân viên không có gì để hủy.\n";
        } else {
            std::string maPL = Helper::nhapChuoi(" - Nhập Mã Phúc Lợi cần HỦY: ");
            if (db.huyGhiDanhPhucLoi(maNV, maPL)) {
                std::cout << " >> Hủy ghi danh thành công.\n";
            } else {
                std::cout << " (!) Hủy thất bại (Mã PL sai hoặc NV chưa đăng ký).\n";
            }
        }
    }
}
// ========================================================

void QuanLyNhanSu::chucNang_ChayBangLuong() {
    Helper::xoaManHinh();
    std::cout << "--- [2.2] Tính Lương Hàng Tháng ---\n";
    std::cout << " (Chức năng này sẽ tính toán lương cho tất cả nhân viên)\n";

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

    std::cout << "\n--- BẢNG LƯƠNG THÁNG (GIẢ ĐỊNH) ---\n";
    std::cout << "+--------+---------------------------+-----------------+\n";
    std::cout << "| Mã NV  | Họ Tên                    | Lương Thực Lĩnh |\n";
    std::cout << "+--------+---------------------------+-----------------+\n";
    
    double tongLuong = 0.0;

    for (const NhanVien* nv : db.getDSNhanVien()) {
        if (nv->getTrangThai() == TrangThaiLamViec::DA_NGHI) continue;
        
        double luong = nv->tinhLuong();
        tongLuong += luong;

        std::cout << "| " << std::left << std::setw(6) << nv->getMaNV()
                  << " | " << std::setw(25) << nv->getHoTen()
                  << " | " << std::right << std::setw(15) << std::fixed << std::setprecision(0) << luong << " |\n";
    }
    
    std::cout << "+--------+---------------------------+-----------------+\n";
    std::cout << "| " << std::left << std::setw(34) << "TỔNG CHI PHÍ LƯƠNG"
              << " | " << std::right << std::setw(15) << std::fixed << std::setprecision(0) << tongLuong << " |\n";
    std::cout << "+--------+---------------------------+-----------------+\n";

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
            default: std::cout << " (!) Lựa chọn không hợp lệ.\n"; break;
        }
        if (!troVe) {
            Helper::dungManHinh();
        }
    }
}

void QuanLyNhanSu::chucNang_BaoCaoNhanSuTheoPhongBan() {
    Helper::xoaManHinh();
    std::cout << "--- [4.1] Báo Cáo Nhân Sự Theo Phòng Ban ---\n";

    const auto& dsPhongBan = db.getDSPhongBan();
    const auto& dsNhanVien = db.getDSNhanVien();

    if (dsPhongBan.empty()) {
        std::cout << " (Chưa có phòng ban nào)\n";
        return;
    }

    std::map<std::string, int> soLuongNV;
    for (const NhanVien* nv : dsNhanVien) {
        if (nv->getTrangThai()!= TrangThaiLamViec::DA_NGHI) {
            soLuongNV[nv->getMaPhongBan()]++;
        }
    }

    std::cout << "+------------+---------------------------+-------------+\n";
    std::cout << "| Mã PB      | Tên Phòng Ban             | Số Lượng NV |\n";
    std::cout << "+------------+---------------------------+-------------+\n";

    for (const PhongBan& pb : dsPhongBan) {
        std::cout << "| " << std::left << std::setw(10) << pb.getMaPB()
                  << " | " << std::setw(25) << pb.getTenPB()
                  << " | " << std::right << std::setw(11) << soLuongNV[pb.getMaPB()] << " |\n";
    }

    std::cout << "| " << std::left << std::setw(10) << "Chưa phân bổ"
              << " | " << std::setw(25) << "(Nhân viên chưa có phòng ban)"
              << " | " << std::right << std::setw(11) << soLuongNV[""] << " |\n";

    std::cout << "+------------+---------------------------+-------------+\n";
}


// ========================================================
// --- HÀM MỚI [4.2] XUẤT FILE CSV ---
void QuanLyNhanSu::chucNang_XuatDanhSachNhanVien() {
    Helper::xoaManHinh();
    std::cout << "--- [4.2] Xuất Danh Sách Nhân Viên (CSV) ---\n";
    std::string tenFile = Helper::nhapChuoi(" - Nhập tên file để xuất (ví dụ: export.csv): ");

    std::ofstream file(tenFile);
    if (!file.is_open()) {
        std::cout << " (!) Không thể tạo file để xuất.\n";
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
    std::cout << " >> Đã xuất thành công danh sách " << db.getDSNhanVien().size()
              << " Nhân viên ra file: " << tenFile << "\n";
}
// ========================================================


void QuanLyNhanSu::thoatChuongTrinh() {
    std::cout << "Bạn có chắc chắn muốn lưu và thoát?\n";
    std::cout << "[1] Đồng ý\n";
    std::cout << "[2] Hủy\n";
    int chon = Helper::nhapSoNguyen(" >> Lựa chọn: ", 1, 2);
    if (chon == 1) {
        std::cout << "Đang lưu tất cả dữ liệu..." << std::endl;
        // --- LƯU DỮ LIỆU KHI THOÁT ---
        db.luuDuLieuVaoFile();
        std::cout << "Đã lưu thành công. Tạm biệt!" << std::endl;
        dangChay = false;
    }
}