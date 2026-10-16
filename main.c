#include <stdio.h>
#include <string.h>

#define MAX_VE 100
#define MAX_VE_PER_ORDER 4

// Cấu trúc lưu trữ thông tin vé Concert
struct VeBan {
    int maVe;
    char tenKhuVuc[20];
    float giaGoc;
    int isEarlyBird; // 1: Được giảm 15%, 0: Giá gốc
};

// Prototype các hàm: Hàm đặt vé trả về số lượng vé sau khi xử lý
int datVeConcert(struct VeBan dsVe[], int soLuong, struct VeBan veMoi);
void hienThiDanhSachVe(const struct VeBan dsVe[], int soLuong);

int main() {
    struct VeBan dsVe[MAX_VE];
    int soLuong = 0;

    printf("=== HỆ THỐNG ĐẶT VÉ CONCERT TICKETBOX ===\n\n");

    // Giả lập khách hàng đặt 2 vé đầu tiên
    struct VeBan ve1 = {101, "VIP", 2000000.0f, 1};
    struct VeBan ve2 = {102, "Zone A", 1200000.0f, 0};

    soLuong = datVeConcert(dsVe, soLuong, ve1);
    soLuong = datVeConcert(dsVe, soLuong, ve2);

    // Giả lập đặt thêm để kiểm tra điều kiện biên hạn ngạch
    struct VeBan ve3 = {103, "Zone A", 1200000.0f, 1};
    struct VeBan ve4 = {104, "GA", 800000.0f, 0};
    struct VeBan ve5 = {105, "GA", 800000.0f, 1};

    soLuong = datVeConcert(dsVe, soLuong, ve3);
    soLuong = datVeConcert(dsVe, soLuong, ve4);
    
    // Thử đặt vé thứ 5 vượt hạn ngạch 4 vé/đơn
    printf("\n--- Thử đặt vé thứ 5 (vượt hạn ngạch) ---\n");
    soLuong = datVeConcert(dsVe, soLuong, ve5);

    // Hiển thị lại giỏ hàng sau khi đặt vé
    printf("\n>>> KẾT QUẢ KIỂM TRA GIỎ HÀNG TRONG MAIN <<<\n");
    hienThiDanhSachVe(dsVe, soLuong);

    return 0;
}

int datVeConcert(struct VeBan dsVe[], int soLuong, struct VeBan veMoi) {
    // 1. Kiểm tra sức chứa bộ nhớ hệ thống
    if (soLuong >= MAX_VE) {
        printf("[LỖI]: Mảng lưu trữ vé của hệ thống đã đầy!\n");
        return soLuong;
    }

    // 2. Kiểm tra hạn ngạch giao dịch (tối đa 4 vé/đơn hàng)
    if (soLuong >= MAX_VE_PER_ORDER) {
        printf("[LỖI]: Đơn hàng đã đạt giới hạn tối đa (%d vé/đơn). Không thể đặt thêm mã vé %d!\n", 
               MAX_VE_PER_ORDER, veMoi.maVe);
        return soLuong;
    }

    // 3. Tính giá thực tế sau khi áp dụng Early Bird (giảm 15%)
    if (veMoi.isEarlyBird == 1) {
        veMoi.giaGoc = veMoi.giaGoc * 0.85f;
    }

    // 4. Lưu vé vào danh sách và tăng số lượng
    dsVe[soLuong] = veMoi;
    soLuong++;

    printf("[THÀNH CÔNG]: Đã thêm vé %d (%s) vào đơn hàng. Tổng vé hiện tại: %d\n", 
           veMoi.maVe, veMoi.tenKhuVuc, soLuong);

    return soLuong;
}

void hienThiDanhSachVe(const struct VeBan dsVe[], int soLuong) {
    if (soLuong == 0) {
        printf("[THÔNG BÁO]: Hiện chưa có vé nào được đặt thành công trong hệ thống!\n");
        return;
    }

    printf("--- DANH SÁCH VÉ ĐÃ ĐẶT (%d vé) ---\n", soLuong);
    for (int i = 0; i < soLuong; i++) {
        printf("STT: %d | Mã vé: %d | Khu vực: %-7s | Giá thanh toán: %.0f VND\n",
               i + 1, dsVe[i].maVe, dsVe[i].tenKhuVuc, dsVe[i].giaGoc);
    }
}