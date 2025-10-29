#include "../include/Database.h"
#include "../include/NhanVien.h"
#include "../include/NVLuongCung.h"
#include "../include/NVHoaHong.h"
#include "../include/NVTheoGio.h"
#include "../include/ChucDanh.h"
#include "../include/PhucLoi.h"
#include "../include/Helper.h"       // Phải include Helper
#include "../include/Date.h"         // Phải include Date
#include "../include/LichSuThayDoi.h" // Phải include LichSuThayDoi
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip> // for std::setw, std::setfill

Database::Database() : autoIncrementMaNV(1) {
    // Constructor
    // Tải dữ liệu ngay khi khởi tạo
    taiDuLieuTuFile();
}

Database::~Database() {
    // Lưu dữ liệu trước khi thoát
    luuDuLieuVaoFile();

    // Dọn dẹp bộ nhớ
    // Vì dsNhanVien là vector con trỏ, phải delete từng đối tượng
    for (NhanVien* nv : dsNhanVien) {
        delete nv;
    }
    dsNhanVien.clear();
}

std::string Database::taoMaNVMoi() {
    // Tạo mã NV tăng dần, ví dụ: NV001, NV002
    std::stringstream ss;
    ss << "NV" << std::setfill('0') << std::setw(3) << autoIncrementMaNV++;
    return ss.str();
}

// ============== TẢI DỮ LIỆU (LOAD) ================

void Database::taiDuLieuTuFile() {
    std::cout << "Đang tải dữ liệu từ file...\n";
    taiPhongBan();
    taiChucDanh();
    taiNhanVien(); 
    taiLichSu();
    taiPhucLoi();
    taiDangKyPhucLoi();
    std::cout << "Tải dữ liệu thành công.\n";
}

//... (Các hàm taiPhongBan, taiChucDanh, taoNhanVienTuLoai, taiNhanVien không đổi)...
void Database::taiPhongBan() {
    std::ifstream file(FILE_PHONGBAN);
    if (!file.is_open()) {
        std::cerr << " (!) Không tìm thấy file " << FILE_PHONGBAN << ", sẽ tạo file mới khi lưu.\n";
        return;
    }

    dsPhongBan.clear();
    std::string line;
    std::getline(file, line); // Bỏ qua dòng header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string maPB, tenPB, maTP;

        std::getline(ss, maPB, ',');
        std::getline(ss, tenPB, ',');
        std::getline(ss, maTP, ',');

        if (!maPB.empty()) {
            dsPhongBan.push_back(PhongBan(maPB, tenPB, maTP));
        }
    }
    file.close();
}

void Database::taiChucDanh() {
    std::ifstream file(FILE_CHUCDANH);
    if (!file.is_open()) {
        std::cerr << " (!) Không tìm thấy file " << FILE_CHUCDANH << ", sẽ tạo file mới khi lưu.\n";
        return;
    }

    dsChucDanh.clear();
    std::string line;
    std::getline(file, line); // Bỏ qua header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string maCD, tenCD, luongCBStr;
        double luongCB = 0.0;

        std::getline(ss, maCD, ',');
        std::getline(ss, tenCD, ',');
        std::getline(ss, luongCBStr, ',');
        
        try {
            luongCB = std::stod(luongCBStr);
        } catch (...) {
            luongCB = 0.0;
        }
        
        if (!maCD.empty()) {
            dsChucDanh.push_back(ChucDanh(maCD, tenCD, luongCB));
        }
    }
    file.close();
}

NhanVien* Database::taoNhanVienTuLoai(LoaiNhanVien loai) {
    switch (loai) {
        case LoaiNhanVien::LUONG_CUNG:
            return new NVLuongCung();
        case LoaiNhanVien::THEO_GIO:
            return new NVTheoGio();
        case LoaiNhanVien::HOA_HONG:
            return new NVHoaHong();
        default:
            return nullptr;
    }
}

void Database::taiNhanVien() {
    std::ifstream file(FILE_NHANVIEN);
    if (!file.is_open()) {
        std::cerr << " (!) Không tìm thấy file " << FILE_NHANVIEN << ", sẽ tạo file mới khi lưu.\n";
        return;
    }

    // Xóa dữ liệu cũ
    for (NhanVien* nv : dsNhanVien) {
        delete nv;
    }
    dsNhanVien.clear();

    std::string line;
    std::getline(file, line); // Bỏ qua header

    int maxId = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string loaiNVStr;
        std::getline(ss, loaiNVStr, '|'); // Đọc trường đầu tiên: Loại NV

        if (loaiNVStr.empty()) { 
            continue; 
        }

        LoaiNhanVien loaiNV;
        
        try { 
            loaiNV = static_cast<LoaiNhanVien>(std::stoi(loaiNVStr));
        } catch (const std::exception& e) { 
            std::cerr << " (!) Lỗi doc file: Loại NV không hợp lệ: " << loaiNVStr << ". Bỏ qua dòng.\n";
            continue;
        }
        
        NhanVien* nv = taoNhanVienTuLoai(loaiNV);
        
        if (nv!= nullptr) {
            nv->docTuFile(ss); 
            dsNhanVien.push_back(nv);

            try {
                int currentId = std::stoi(nv->getMaNV().substr(2)); 
                if (currentId > maxId) {
                    maxId = currentId;
                }
            } catch (...) {
                // Bỏ qua nếu mã NV không đúng định dạng
            }
        }
    }
    file.close();
    autoIncrementMaNV = maxId + 1; 
}

// HÀM MỚI
void Database::taiLichSu() {
    std::ifstream file(FILE_LICHSU);
    if (!file.is_open()) {
        std::cerr << " (!) Không tìm thấy file " << FILE_LICHSU << ", sẽ tạo file mới khi lưu.\n";
        return;
    }

    dsLichSu.clear();
    std::string line;
    std::getline(file, line); // Bỏ qua header

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string maNV, ngayStr, moTa, giaTriCu, giaTriMoi;

        std::getline(ss, maNV, ',');
        std::getline(ss, ngayStr, ',');
        std::getline(ss, moTa, ',');
        std::getline(ss, giaTriCu, ',');
        std::getline(ss, giaTriMoi, ',');

        // Chuyển đổi chuỗi ngày thành đối tượng Date
        Date ngay; // Khởi tạo ngày mặc định
        try {
            int d, m, y;
            char slash1, slash2;
            std::stringstream date_ss(ngayStr);
            date_ss >> d >> slash1 >> m >> slash2 >> y;
            
            if (date_ss.fail() || slash1 != '/' || slash2 != '/') {
                ngay.setDate(1, 1, 2000); // Ngày mặc định nếu lỗi
            } else {
                ngay.setDate(d, m, y);
            }
        } catch (const std::exception& e) {
            ngay.setDate(1, 1, 2000); // Ngày mặc định nếu lỗi
        }
        // Thêm vào map
        dsLichSu[maNV].emplace_back(ngay, moTa, giaTriCu, giaTriMoi);
    }
    file.close();
}


// ============== LƯU DỮ LIỆU (SAVE) ================

void Database::luuDuLieuVaoFile() {
    std::cout << "\nĐang lưu dữ liệu ra file...\n";
    luuPhongBan();
    luuChucDanh(); // Gọi 1 lần
    luuNhanVien();
    luuLichSu(); 
    // luuChucDanh(); // <-- XÓA DÒNG BỊ LẶP NÀY
    luuPhucLoi();
    luuDangKyPhucLoi();
    std::cout << "Lưu dữ liệu thành công.\n";
}

//... (Các hàm luuPhongBan, luuChucDanh, luuNhanVien không đổi)...
void Database::luuPhongBan() const {
    std::ofstream file(FILE_PHONGBAN);
    if (!file.is_open()) {
        std::cerr << " (!) Lỗi: Không thể mở file " << FILE_PHONGBAN << " để ghi.\n";
        return;
    }
    file << "MaPB,TenPB,MaTruongPhong\n";
    for (const PhongBan& pb : dsPhongBan) {
        file << pb.getMaPB() << ","
             << pb.getTenPB() << ","
             << pb.getMaTruongPhong() << "\n";
    }
    file.close();
}

void Database::luuChucDanh() const {
    std::ofstream file(FILE_CHUCDANH);
    if (!file.is_open()) {
        std::cerr << " (!) Lỗi: Không thể mở file " << FILE_CHUCDANH << " để ghi.\n";
        return;
    }
    file << "MaCD,TenCD,LuongCoBan\n";
    for (const ChucDanh& cd : dsChucDanh) {
        file << cd.getMaChucDanh() << ","
             << cd.getTenChucDanh() << ","
             << cd.getLuongCoBan() << "\n"; // <-- SỬA LỖI Ở ĐÂY (thay "0" bằng cd.getLuongCoBan())
    }
    file.close();
}

void Database::luuNhanVien() const {
    std::ofstream file(FILE_NHANVIEN);
    if (!file.is_open()) {
        std::cerr << " (!) Lỗi: Không thể mở file " << FILE_NHANVIEN << " để ghi.\n";
        return;
    }

    file << "LoaiNV,HoTen,CCCD,DiaChi,SDT,Email,NgaySinh,MaNV,NgayVaoLam,TrangThai,MaPB,MaCD,TruongRieng...\n";

    for (const NhanVien* nv : dsNhanVien) {
        nv->luuVaoFile(file);
    }
    file.close();
}

// HÀM MỚI
void Database::luuLichSu() const {
    std::ofstream file(FILE_LICHSU);
    if (!file.is_open()) {
        std::cerr << " (!) Lỗi: Không thể mở file " << FILE_LICHSU << " để ghi.\n";
        return;
    }

    file << "MaNV,Ngay,MoTa,GiaTriCu,GiaTriMoi\n";
    for (const auto& pair : dsLichSu) {
        const std::string& maNV = pair.first;
        const auto& lichSuVector = pair.second;
        for (const auto& ghiNhan : lichSuVector) {
            file << maNV << ","
                 << ghiNhan.ngayThayDoi.toString() << ","
                 << ghiNhan.moTa << ","
                 << ghiNhan.giaTriCu << ","
                 << ghiNhan.giaTriMoi << "\n";
        }
    }
    file.close();
}


// ============== QUẢN LÝ NHÂN VIÊN ================
//... (Các hàm quản lý nhân viên, phòng ban, chức danh không đổi)...
void Database::themNhanVien(NhanVien* nv) {
    nv->setMaNV(taoMaNVMoi());
    dsNhanVien.push_back(nv);
    std::cout << " >> Đã thêm nhân viên mới với mã: " << nv->getMaNV() << "\n";
}

NhanVien* Database::timNhanVienTheoMa(const std::string& maNV) {
    for (NhanVien* nv : dsNhanVien) {
        if (nv->getMaNV() == maNV) {
            return nv;
        }
    }
    return nullptr; 
}

bool Database::xoaNhanVienTheoMa(const std::string& maNV) {
    for (auto it = dsNhanVien.begin(); it!= dsNhanVien.end(); ++it) {
        if ((*it)->getMaNV() == maNV) {
            delete *it; 
            dsNhanVien.erase(it); 
            return true;
        }
    }
    return false; 
}

const std::vector<NhanVien*>& Database::getDSNhanVien() const {
    return dsNhanVien;
}

void Database::themPhongBan(const PhongBan& pb) {
    dsPhongBan.push_back(pb);
}

PhongBan* Database::timPhongBanTheoMa(const std::string& maPB) {
    for (PhongBan& pb : dsPhongBan) {
        if (pb.getMaPB() == maPB) {
            return &pb;
        }
    }
    return nullptr;
}

const std::vector<PhongBan>& Database::getDSPhongBan() const {
    return dsPhongBan;
}

void Database::themChucDanh(const ChucDanh& cd) {
    dsChucDanh.push_back(cd);
}

ChucDanh* Database::timChucDanhTheoMa(const std::string& maCD) {
    for (ChucDanh& cd : dsChucDanh) {
        if (cd.getMaChucDanh() == maCD) {
            return &cd;
        }
    }
    return nullptr;
}

const std::vector<ChucDanh>& Database::getDSChucDanh() const {
    return dsChucDanh;
}

// ============== QUẢN LÝ LỊCH SỬ (CÁC HÀM MỚI) ================

void Database::themGhiNhanLichSu(const std::string& maNV, const std::string& moTa, const std::string& giaTriCu, const std::string& giaTriMoi) {
    Date homNay = Date::layNgayHienTai();
    dsLichSu[maNV].emplace_back(homNay, moTa, giaTriCu, giaTriMoi);
}

const std::vector<LichSuThayDoi>* Database::layLichSuCuaNV(const std::string& maNV) const {
    auto it = dsLichSu.find(maNV);
    if (it!= dsLichSu.end()) {
        return &(it->second); // Trả về con trỏ tới vector lịch sử
    }
    return nullptr; // Không tìm thấy lịch sử cho NV này
}


// --- TẤT CẢ CÁC HÀM BỊ TRÙNG LẶP ĐÃ BỊ XÓA KHỎI ĐÂY ---
// --- BẮT ĐẦU CÁC HÀM MỚI (PHÚC LỢI) MÀ BẠN CHƯA CÓ ---

void Database::taiPhucLoi() {
    std::ifstream file(FILE_PHUCLOI);
    if (!file.is_open()) return;
    danhSachPhucLoi.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string maPL, tenPL, chiPhiStr;
        std::getline(ss, maPL, ',');
        std::getline(ss, tenPL, ',');
        std::getline(ss, chiPhiStr, ',');
        try {
            danhSachPhucLoi.push_back(PhucLoi(maPL, tenPL, std::stod(chiPhiStr)));
        } catch (...) { /* Bỏ qua dòng lỗi */ }
    }
    file.close();
}

void Database::luuPhucLoi() {
    std::ofstream file(FILE_PHUCLOI);
    for (const auto& pl : danhSachPhucLoi) {
        // Giả sử PhucLoi có hàm toStringCSV() giống ChucDanh
        // Nếu không, bạn cần triển khai nó:
        file << pl.getMaPhucLoi() << "," << pl.getTenPhucLoi() << "," << pl.getChiPhiHangThang() << "\n";
    }
    file.close();
}

void Database::taiDangKyPhucLoi() {
    std::ifstream file(FILE_DANGKY_PHUCLOI);
    if (!file.is_open()) return;
    danhSachDangKyPhucLoi.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string maNV, maPL;
        std::getline(ss, maNV, ',');
        std::getline(ss, maPL, ',');
        danhSachDangKyPhucLoi[maNV].push_back(maPL);
    }
    file.close();
}

void Database::luuDangKyPhucLoi() {
    std::ofstream file(FILE_DANGKY_PHUCLOI);
    for (const auto& pair : danhSachDangKyPhucLoi) {
        const std::string& maNV = pair.first;
        for (const std::string& maPL : pair.second) {
            file << maNV << "," << maPL << "\n";
        }
    }
    file.close();
}

// =======================================================
// --- TRIEN KHAI CAC HAM LOGIC (PHÚC LỢI) ---
// =======================================================

const std::vector<PhucLoi>& Database::getDSPhucLoi() const {
    return danhSachPhucLoi;
}

PhucLoi* Database::timPhucLoiTheoMa(const std::string& maPL) {
    for (auto& pl : danhSachPhucLoi) {
        if (pl.getMaPhucLoi() == maPL) return &pl;
    }
    return nullptr;
}

void Database::themPhucLoi(const PhucLoi& pl) {
    if (timPhucLoiTheoMa(pl.getMaPhucLoi()) == nullptr) {
        danhSachPhucLoi.push_back(pl);
    }
}

void Database::xoaPhucLoi(const std::string& maPL) {
    // Xóa khỏi danh sách chính
    danhSachPhucLoi.erase(
        std::remove_if(danhSachPhucLoi.begin(), danhSachPhucLoi.end(), 
            [&](const PhucLoi& pl) { return pl.getMaPhucLoi() == maPL; }),
        danhSachPhucLoi.end()
    );
    // Xóa khỏi tất cả các đăng ký
    for (auto& pair : danhSachDangKyPhucLoi) {
        pair.second.erase(
            std::remove(pair.second.begin(), pair.second.end(), maPL),
            pair.second.end()
        );
    }
}

std::vector<PhucLoi*> Database::getPhucLoiCuaNhanVien(const std::string& maNV) {
    std::vector<PhucLoi*> ds;
    auto it = danhSachDangKyPhucLoi.find(maNV);
    if (it != danhSachDangKyPhucLoi.end()) {
        for (const std::string& maPL : it->second) {
            PhucLoi* pl = timPhucLoiTheoMa(maPL);
            if (pl) ds.push_back(pl);
        }
    }
    return ds;
}

bool Database::ghiDanhPhucLoi(const std::string& maNV, const std::string& maPL) {
    if (timNhanVienTheoMa(maNV) == nullptr) {
        std::cout << " (!) Không tìm thấy Nhân Viên.\n"; return false;
    }
    if (timPhucLoiTheoMa(maPL) == nullptr) {
        std::cout << " (!) Không tìm thấy Phúc Lợi.\n"; return false;
    }
    // Kiểm tra đã đăng ký chưa
    auto& ds = danhSachDangKyPhucLoi[maNV];
    for (const std::string& ma : ds) {
        if (ma == maPL) {
            std::cout << " (!) Nhân viên đã đăng ký gói này rồi.\n";
            return false;
        }
    }
    ds.push_back(maPL);
    return true;
}

bool Database::huyGhiDanhPhucLoi(const std::string& maNV, const std::string& maPL) {
    auto it = danhSachDangKyPhucLoi.find(maNV);
    if (it != danhSachDangKyPhucLoi.end()) {
        auto& ds = it->second;
        auto ds_it = std::find(ds.begin(), ds.end(), maPL);
        if (ds_it != ds.end()) {
            ds.erase(ds_it);
            return true;
        }
    }
    return false;
}