#include "../include/Database.h"
#include "../include/NhanVien.h"
#include "../include/NVLuongCung.h"
#include "../include/NVHoaHong.h"
#include "../include/NVTheoGio.h"
#include "../include/ChucDanh.h"
#include "../include/PhucLoi.h"
#include "../include/Account.h" 
#include "../include/Helper.h"
#include "../include/Date.h"
#include "../include/LichSuThayDoi.h" 
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


Database::Database() : autoIncrementMaNV(1) {}
Database::~Database() {
    for (NhanVien* nv : dsNhanVien) { delete nv; }
    dsNhanVien.clear();
    for (Account* acc : dsTaiKhoan) { delete acc; } 
    dsTaiKhoan.clear();
}

string Database::taoMaNVMoi() {
    stringstream ss;
    ss << "NV" << setfill('0') << setw(3) << autoIncrementMaNV++;
    return ss.str();
}
void Database::taiDuLieuTuFile() {
    cout << "Đang tải dữ liệu từ file...\n";
    taiPhongBan();
    taiChucDanh();
    taiNhanVien(); 
    taiLichSu();
    taiPhucLoi();
    taiDangKyPhucLoi();
    taiTaiKhoan(); 
    kiemTraTaiKhoanChuTich(); 
    cout << "Tải dữ liệu thành công.\n";
}

void Database::taiPhongBan() {
    ifstream file(FILE_PHONGBAN);
    if (!file.is_open()) { return; }
    dsPhongBan.clear();
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maPB, tenPB, maTP;
        getline(ss, maPB, ',');
        getline(ss, tenPB, ',');
        getline(ss, maTP, ',');
        if (!maPB.empty()) { dsPhongBan.push_back(PhongBan(maPB, tenPB, maTP)); }
    }
    file.close();
}

void Database::taiChucDanh() {
    ifstream file(FILE_CHUCDANH);
    if (!file.is_open()) { return; }
    dsChucDanh.clear();
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maCD, tenCD, luongCBStr;
        double luongCB = 0.0;
        getline(ss, maCD, ',');
        getline(ss, tenCD, ',');
        getline(ss, luongCBStr, ',');
        try { luongCB = luongCBStr.empty() ? 0.0 : stod(luongCBStr); } 
        catch (...) { luongCB = 0.0; }
        if (!maCD.empty()) { dsChucDanh.push_back(ChucDanh(maCD, tenCD, luongCB)); }
    }
    file.close();
}

NhanVien* Database::taoNhanVienTuLoai(LoaiNhanVien loai) {
    switch (loai) {
        case LoaiNhanVien::LUONG_CUNG: return new NVLuongCung();
        case LoaiNhanVien::THEO_GIO: return new NVTheoGio();
        case LoaiNhanVien::HOA_HONG: return new NVHoaHong();
        default: return nullptr;
    }
}

void Database::taiNhanVien() {
    ifstream file(FILE_NHANVIEN);
    if (!file.is_open()) { return; }
    for (NhanVien* nv : dsNhanVien) { delete nv; }
    dsNhanVien.clear();
    string line;
    getline(file, line); 
    int maxId = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string loaiNVStr;
        getline(ss, loaiNVStr, ',');
        if (loaiNVStr.empty()) { continue; }
        LoaiNhanVien loaiNV;
        try { loaiNV = static_cast<LoaiNhanVien>(stoi(loaiNVStr)); } 
        catch (const exception& e) { continue; }
        NhanVien* nv = taoNhanVienTuLoai(loaiNV);
        if (nv!= nullptr) {
            nv->docTuFile(ss); 
            dsNhanVien.push_back(nv);
            try {
                if (!nv->getMaNV().empty() && nv->getMaNV().length() > 2) {
                    int currentId = stoi(nv->getMaNV().substr(2)); 
                    if (currentId > maxId) { maxId = currentId; }
                }
            } catch (...) { }
        }
    }
    file.close();
    autoIncrementMaNV = maxId + 1; 
}

void Database::taiLichSu() {
    ifstream file(FILE_LICHSU);
    if (!file.is_open()) { return; }
    dsLichSu.clear();
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maNV, ngayStr, moTa, giaTriCu, giaTriMoi;
        getline(ss, maNV, ',');
        getline(ss, ngayStr, ',');
        getline(ss, moTa, ',');
        getline(ss, giaTriCu, ',');
        getline(ss, giaTriMoi, ',');
        
        Date dateUtil; 
        Date ngay = dateUtil.fromString(ngayStr);
        dsLichSu[maNV].emplace_back(ngay, moTa, giaTriCu, giaTriMoi);
    }
    file.close();
}

void Database::taiPhucLoi() {
    ifstream file(FILE_PHUCLOI);
    if (!file.is_open()) return;
    danhSachPhucLoi.clear();
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maPL, tenPL, chiPhiStr;
        getline(ss, maPL, ',');
        getline(ss, tenPL, ',');
        getline(ss, chiPhiStr, ',');
        try {
            danhSachPhucLoi.push_back(PhucLoi(maPL, tenPL, stod(chiPhiStr)));
        } catch (...) { }
    }
    file.close();
}

void Database::taiDangKyPhucLoi() {
    ifstream file(FILE_DANGKY_PHUCLOI);
    if (!file.is_open()) return;
    danhSachDangKyPhucLoi.clear();
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maNV, maPL;
        getline(ss, maNV, ',');
        getline(ss, maPL, ',');
        danhSachDangKyPhucLoi[maNV].push_back(maPL);
    }
    file.close();
}

void Database::taiTaiKhoan() {
    ifstream file(FILE_ACCOUNT);
    if (!file.is_open()) { return; }
    for (Account* acc : dsTaiKhoan) { delete acc; }
    dsTaiKhoan.clear();
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Account* acc = new Account();
        acc->docTuFile(ss);
        dsTaiKhoan.push_back(acc);
    }
    file.close();
}

void Database::luuDuLieuVaoFile() {
    cout << "\nĐang lưu dữ liệu ra file...\n";
    luuPhongBan();
    luuChucDanh();
    luuNhanVien();
    luuLichSu(); 
    luuPhucLoi();
    luuDangKyPhucLoi();
    luuTaiKhoan(); 
    cout << "Lưu dữ liệu thành công.\n";
}
void Database::importNhanVienTuFile(const string& tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << " (!) Lỗi: Không thể mở file '" << tenFile << "'.\n";
        return;
    }
    string line;
    int count = 0;
    cout << " >> Đang xử lý dữ liệu...\n";

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> row;
        while (getline(ss, segment, ',')) { row.push_back(segment); }

        if (row.size() < 9) continue; 

        try {
            int loai = stoi(row[0]);
            string ten = row[1];
            string cccd = row[2];
            string dc = row[3];
            string sdt = row[4];
            string nsStr = row[5];
            string maPB = row[6];
            string maCD = row[7];
        
            if (timPhongBanTheoMa(maPB) == nullptr) {
                string tenPBMoi = "Phong " + maPB;
                PhongBan pb(maPB, tenPBMoi, "Chua bo nhiem");
                themPhongBan(pb);
                cout << " >> (Auto) Đã tạo mới phòng ban: " << maPB << "\n";
            }
            Date dateUtil;
            Date ns = dateUtil.fromString(nsStr);
            Date nvl = dateUtil.layNgayHienTai(); 

            NhanVien* nv = nullptr;

            if (loai == 1) {
                double luong = stod(row[8]);
                nv = new NVLuongCung("", ten, cccd, dc, sdt, "", ns, nvl, TrangThaiLamViec::CHINH_THUC, maPB, maCD, luong);
            } 
            else if (loai == 2) { 
                double luongGio = stod(row[8]);
                double soGio = (row.size() > 9) ? stod(row[9]) : 0; 
                nv = new NVTheoGio("", ten, cccd, dc, sdt, "", ns, nvl, TrangThaiLamViec::THU_VIEC, maPB, maCD, luongGio, soGio);
            } 
            else if (loai == 3) {
                double luongCB = stod(row[8]);
                double doanhSo = (row.size() > 9) ? stod(row[9]) : 0;
                double tyLe = (row.size() > 10) ? stod(row[10]) : 0.0;
                nv = new NVHoaHong("", ten, cccd, dc, sdt, "", ns, nvl, TrangThaiLamViec::THU_VIEC, maPB, maCD, luongCB, doanhSo, tyLe);
            }

            if (nv != nullptr) {
                themNhanVien(nv, Role::NHAN_VIEN); 
                count++;
            }
        } catch (...) { 
        }
    }
    file.close();
    cout << " >> Hoàn tất! Đã nhập thành công " << count << " nhân viên từ file.\n";
}
void Database::luuPhongBan() const {
    ofstream file(FILE_PHONGBAN);
    if (!file.is_open()) { return; }
    file << "MaPB,TenPB,MaTruongPhong\n";
    for (const PhongBan& pb : dsPhongBan) {
        file << pb.getMaPB() << "," << pb.getTenPB() << "," << pb.getMaTruongPhong() << "\n";
    }
    file.close();
}

void Database::luuChucDanh() const {
    ofstream file(FILE_CHUCDANH);
    if (!file.is_open()) { return; }
    file << "MaCD,TenCD,LuongCoBan\n";
    for (const ChucDanh& cd : dsChucDanh) {
        file << cd.getMaChucDanh() << "," << cd.getTenChucDanh() << "," << cd.getLuongCoBan() << "\n";
    }
    file.close();
}

void Database::luuNhanVien() const {
    ofstream file(FILE_NHANVIEN);
    if (!file.is_open()) { return; }
    file << "LoaiNV,HoTen,CCCD,DiaChi,SDT,Email,NgaySinh,MaNV,NgayVaoLam,TrangThai,MaPB,MaCD,TruongRieng...\n";
    for (const NhanVien* nv : dsNhanVien) {
        nv->luuVaoFile(file);
    }
    file.close();
}

void Database::luuLichSu() const {
    ofstream file(FILE_LICHSU);
    if (!file.is_open()) { return; }
    file << "MaNV,Ngay,MoTa,GiaTriCu,GiaTriMoi\n";
    for (const auto& pair : dsLichSu) {
        const string& maNV = pair.first;
        for (const auto& ghiNhan : pair.second) {
            file << maNV << "," << ghiNhan.ngayThayDoi.toString() << "," << ghiNhan.moTa << ","
                 << ghiNhan.giaTriCu << "," << ghiNhan.giaTriMoi << "\n";
        }
    }
    file.close();
}

void Database::luuPhucLoi() {
    ofstream file(FILE_PHUCLOI);
    if (!file.is_open()) return;
    file << "MaPL,TenPL,ChiPhi\n";
    for (const auto& pl : danhSachPhucLoi) {
        file << pl.getMaPhucLoi() << "," << pl.getTenPhucLoi() << "," << pl.getChiPhiHangThang() << "\n";
    }
    file.close();
}

void Database::luuDangKyPhucLoi() {
    ofstream file(FILE_DANGKY_PHUCLOI);
    if (!file.is_open()) return;
    file << "MaNV,MaPL\n";
    for (const auto& pair : danhSachDangKyPhucLoi) {
        for (const string& maPL : pair.second) {
            file << pair.first << "," << maPL << "\n";
        }
    }
    file.close();
}

void Database::luuTaiKhoan() const {
    ofstream file(FILE_ACCOUNT);
    if (!file.is_open()) { return; }
    file << "Username,Password,Role,MaNV\n";
    for (const Account* acc : dsTaiKhoan) {
        acc->luuVaoFile(file);
    }
    file.close();
}

// ============== QUẢN LÝ TÀI KHOẢN ================

Account* Database::xacThucNguoiDung(const string& username, const string& password) {
    for (Account* acc : dsTaiKhoan) {
        if (acc->getUsername() == username && acc->kiemTraMatKhau(password)) {
            return acc; 
        }
    }
    return nullptr; 
}

bool Database::tenEmailDaTonTai(const string& email) const {
    for (const Account* acc : dsTaiKhoan) {
        if (acc->getUsername() == email) {
            return true;
        }
    }
    return false;
}
void Database::taoTaiKhoanTuDong(NhanVien* nv, Role role) {
    Helper helper; 
    
    string hoTen = nv->getHoTen();
    Date ngaySinh = nv->getNgaySinh();
    string tenChuanHoa = helper.chuanHoaTen(hoTen);
    string maNV = nv->getMaNV();
    string email = helper.taoEmail(tenChuanHoa, ngaySinh, maNV, false);
    string password = helper.taoPassword(ngaySinh, maNV, false);

    // 2. Kiểm tra trùng lặp
    if (tenEmailDaTonTai(email)) {
        cout << " (!) Email cơ bản bị trùng. Đang thêm Mã NV...\n";
        email = helper.taoEmail(tenChuanHoa, ngaySinh, maNV, true);
        password = helper.taoPassword(ngaySinh, maNV, true);
    }
    
    if (role == Role::TRUONG_PHONG) {
        PhongBan* pb = timPhongBanTheoMa(nv->getMaPhongBan());
        if (pb != nullptr) {
            if (pb->getMaTruongPhong() == "" || pb->getMaTruongPhong() == "Chưa bổ nhiệm") {
                pb->setMaTruongPhong(maNV);
                cout << " >> Đã bổ nhiệm " << maNV << " làm Trưởng phòng " << pb->getMaPB() << ".\n";
            } else if (pb->getMaTruongPhong() != maNV) {
                cout << " (!) Cảnh báo: Phòng " << pb->getMaPB() << " đã có Trưởng phòng (" << pb->getMaTruongPhong() << ").\n";
                cout << "     Nhân viên này vẫn sẽ có vai trò Trưởng Phòng, nhưng không được gán làm quản lý phòng ban này.\n";
            }
        } 
    }

    cout << " >> Đang tạo tài khoản tự động...\n";
    cout << "    - Tên đăng nhập (Email): " << email << "\n";
    cout << "    - Mật khẩu: " << password << "\n";
    
    nv->setEmail(email);
    Account* accMoi = new Account(email, password, role, maNV);
    dsTaiKhoan.push_back(accMoi);
}

void Database::kiemTraTaiKhoanChuTich() {
    bool daCo = false;
    for (Account* acc : dsTaiKhoan) {
        if (acc->getUsername() == "thanhchutich1604@team4.group") {
            daCo = true;
            break;
        }
    }
    if (!daCo) {
        cout << " (!) Phát hiện chưa có tài khoản Chủ Tịch. Đang tạo tài khoản mặc định...\n";
        Account* chuTich = new Account("thanhchutich1604@team4.group", "16042006", Role::CHU_TICH, "NV000");
        dsTaiKhoan.push_back(chuTich);
    }
}

void Database::themNhanVien(NhanVien* nv, Role role) {
    nv->setMaNV(taoMaNVMoi()); 
    dsNhanVien.push_back(nv);
    cout << " >> Đã thêm nhân viên mới với mã: " << nv->getMaNV() << "\n";
    taoTaiKhoanTuDong(nv, role); 
}

NhanVien* Database::timNhanVienTheoMa(const string& maNV) {
    for (NhanVien* nv : dsNhanVien) {
        if (nv->getMaNV() == maNV) return nv;
    }
    return nullptr; 
}

bool Database::xoaNhanVienTheoMa(const string& maNV) {
    for (auto it = dsNhanVien.begin(); it!= dsNhanVien.end(); ++it) {
        if ((*it)->getMaNV() == maNV) {
            delete *it; 
            dsNhanVien.erase(it); 
            return true;
        }
    }
    return false; 
}

void Database::thayTheNhanVien(NhanVien* nvMoi) {
    for (size_t i = 0; i < dsNhanVien.size(); ++i) {
        if (dsNhanVien[i]->getMaNV() == nvMoi->getMaNV()) {
            delete dsNhanVien[i];
            dsNhanVien[i] = nvMoi;
            return;
        }
    }
}


const vector<NhanVien*>& Database::getDSNhanVien() const { return dsNhanVien; }
void Database::themPhongBan(const PhongBan& pb) { dsPhongBan.push_back(pb); }
PhongBan* Database::timPhongBanTheoMa(const string& maPB) {
    for (PhongBan& pb : dsPhongBan) {
        if (pb.getMaPB() == maPB) return &pb;
    }
    return nullptr;
}
const vector<PhongBan>& Database::getDSPhongBan() const { return dsPhongBan; }
void Database::themChucDanh(const ChucDanh& cd) { dsChucDanh.push_back(cd); }
ChucDanh* Database::timChucDanhTheoMa(const string& maCD) {
    for (ChucDanh& cd : dsChucDanh) {
        if (cd.getMaChucDanh() == maCD) return &cd;
    }
    return nullptr;
}
const vector<ChucDanh>& Database::getDSChucDanh() const { return dsChucDanh; }

void Database::themGhiNhanLichSu(const string& maNV, const string& moTa, const string& giaTriCu, const string& giaTriMoi) {
    Date dateUtil; 
    dsLichSu[maNV].emplace_back(dateUtil.layNgayHienTai(), moTa, giaTriCu, giaTriMoi);
}

const vector<LichSuThayDoi>* Database::layLichSuCuaNV(const string& maNV) const {
    auto it = dsLichSu.find(maNV);
    if (it!= dsLichSu.end()) return &(it->second);
    return nullptr;
}
const vector<PhucLoi>& Database::getDSPhucLoi() const { return danhSachPhucLoi; }
PhucLoi* Database::timPhucLoiTheoMa(const string& maPL) {
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
void Database::xoaPhucLoi(const string& maPL) {
    danhSachPhucLoi.erase(
        remove_if(danhSachPhucLoi.begin(), danhSachPhucLoi.end(), 
            [&](const PhucLoi& pl) { return pl.getMaPhucLoi() == maPL; }),
        danhSachPhucLoi.end()
    );
    for (auto& pair : danhSachDangKyPhucLoi) {
        pair.second.erase(
            remove(pair.second.begin(), pair.second.end(), maPL),
            pair.second.end()
        );
    }
}
vector<PhucLoi*> Database::getPhucLoiCuaNhanVien(const string& maNV) {
    vector<PhucLoi*> ds;
    auto it = danhSachDangKyPhucLoi.find(maNV);
    if (it != danhSachDangKyPhucLoi.end()) {
        for (const string& maPL : it->second) {
            PhucLoi* pl = timPhucLoiTheoMa(maPL);
            if (pl) ds.push_back(pl);
        }
    }
    return ds;
}
bool Database::ghiDanhPhucLoi(const string& maNV, const string& maPL) {
    if (timNhanVienTheoMa(maNV) == nullptr) return false;
    if (timPhucLoiTheoMa(maPL) == nullptr) return false;
    auto& ds = danhSachDangKyPhucLoi[maNV];
    for (const string& ma : ds) {
        if (ma == maPL) return false;
    }
    ds.push_back(maPL);
    return true;
}
bool Database::huyGhiDanhPhucLoi(const string& maNV, const string& maPL) {
    auto it = danhSachDangKyPhucLoi.find(maNV);
    if (it != danhSachDangKyPhucLoi.end()) {
        auto& ds = it->second;
        auto ds_it = find(ds.begin(), ds.end(), maPL);
        if (ds_it != ds.end()) {
            ds.erase(ds_it);
            return true;
        }
    }
    return false;
}
Account* Database::timTaiKhoanTheoMaNV(const string& maNV) {
    for (Account* acc : dsTaiKhoan) {
        if (acc->getMaNhanVien() == maNV) {
            return acc;
        }
    }
    return nullptr;
}

void Database::capNhatVaiTro(NhanVien* nv, Account* acc, Role vaiTroMoi) {
    Helper helper;
    Role vaiTroCu = acc->getRole();
    string maNV = nv->getMaNV();
    string maPB = nv->getMaPhongBan();
    if (vaiTroCu == Role::TRUONG_PHONG && vaiTroMoi != Role::TRUONG_PHONG) {
        PhongBan* pb = timPhongBanTheoMa(maPB);
        if (pb != nullptr && pb->getMaTruongPhong() == maNV) {
            pb->setMaTruongPhong("Chưa bổ nhiệm");
            cout << " >> (Hệ thống) Đã gỡ " << maNV << " khỏi vị trí Trưởng phòng " << maPB << ".\n";
        }
    }
    if (vaiTroMoi == Role::TRUONG_PHONG) {
        PhongBan* pb = timPhongBanTheoMa(maPB);
        
        if (pb == nullptr) {
            cout << " (!) Lỗi: Phòng ban " << maPB << " không tồn tại. Bổ nhiệm thất bại.\n";
            return; 
        }
        string maTPHienTai = pb->getMaTruongPhong();
        if (maTPHienTai == "" || maTPHienTai == "Chưa bổ nhiệm" || maTPHienTai == "Chua bo nhiem") {
            pb->setMaTruongPhong(maNV);
            cout << " >> (Hệ thống) Đã bổ nhiệm " << maNV << " làm Trưởng phòng " << maPB << ".\n";
        } 
        else if (maTPHienTai == maNV) {
            cout << " (Nhân viên này đã là Trưởng phòng " << maPB << ".)\n";
        }
        else {
            cout << " [!] Phòng " << maPB << " đang có Trưởng phòng là: " << maTPHienTai << ".\n";
            cout << "     Đang tiến hành thay thế...\n";
            NhanVien* nvCu = timNhanVienTheoMa(maTPHienTai);
            Account* accCu = timTaiKhoanTheoMaNV(maTPHienTai);

            if (nvCu && accCu) {
                capNhatVaiTro(nvCu, accCu, Role::NHAN_VIEN); 
                nvCu->setTrangThai(TrangThaiLamViec::CHINH_THUC);
                cout << " >> Đã chuyển " << maTPHienTai << " xuống làm Nhân viên chính thức.\n";
            } else {
                cout << " (!) Không tìm thấy hồ sơ Trưởng phòng cũ. Cưỡng chế ghi đè.\n";
            }
            pb->setMaTruongPhong(maNV);
            cout << " >> Đã bổ nhiệm TÂN TRƯỞNG PHÒNG: " << maNV << ".\n";
        }
    }
    acc->setRole(vaiTroMoi); 
    if ( (vaiTroMoi == Role::TRUONG_PHONG || vaiTroMoi == Role::KE_TOAN) && 
         (nv->getTrangThai() == TrangThaiLamViec::THU_VIEC) ) {
        nv->setTrangThai(TrangThaiLamViec::CHINH_THUC);
        cout << " >> (Hệ thống) Đã tự động thăng cấp NV lên 'Chính thức'.\n";
    }
    if (vaiTroMoi == Role::KE_TOAN) {
        nv->setMaPhongBan("KETOAN");
        cout << " >> (Hệ thống) Đã tự động gán phòng ban là 'KETOAN'.\n";
    }
}
Account* Database::timTaiKhoanDauTienTheoVaiTro(Role role) {
    for (Account* acc : dsTaiKhoan) {
        if (acc->getRole() == role) {
            return acc;
        }
    }
    return nullptr; 
}
void Database::xoaTaiKhoan(const string& maNV) {
    auto it = remove_if(dsTaiKhoan.begin(), dsTaiKhoan.end(), [&](Account* acc) {
        if (acc->getMaNhanVien() == maNV) {
            delete acc;
            return true; 
        }
        return false;
    });

    if (it != dsTaiKhoan.end()) {
        dsTaiKhoan.erase(it, dsTaiKhoan.end());
        cout << " >> (Hệ thống) Đã xóa tài khoản đăng nhập của nhân viên " << maNV << ".\n";
    } else {
        cout << " >> (Hệ thống) Không tìm thấy tài khoản để xóa (có thể đã xóa trước đó).\n";
    }
}
const vector<Account*>& Database::getDSTaiKhoan() const {
    return dsTaiKhoan;
}