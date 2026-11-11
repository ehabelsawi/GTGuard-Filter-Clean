#include "IFMacroMenuAutoSkill.h"
#include <chrono>
#include <iostream>

// Test hiệu suất tìm quái
void TestMonsterFindingPerformance() {
    CIFMacroMenuAutoSkill* autoSkill = nullptr; // Giả sử có instance
    
    // Test phiên bản cũ
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        // Gọi hàm cũ (nếu có)
        // autoSkill->GetNearMonsterID_Old();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_old = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test phiên bản mới
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        // autoSkill->GetNearMonsterID();
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_new = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Old version: " << duration_old.count() << " microseconds" << std::endl;
    std::cout << "New version: " << duration_new.count() << " microseconds" << std::endl;
    std::cout << "Improvement: " << (duration_old.count() - duration_new.count()) * 100.0 / duration_old.count() << "%" << std::endl;
}

// Test hiệu suất tìm skill
void TestSkillFindingPerformance() {
    CIFMacroMenuAutoSkill* autoSkill = nullptr;
    
    // Test phiên bản cũ
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        // autoSkill->FindAttackSkillSlot_Old();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_old = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test phiên bản mới
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        // autoSkill->FindAttackSkillSlot();
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_new = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Skill finding - Old: " << duration_old.count() << " microseconds" << std::endl;
    std::cout << "Skill finding - New: " << duration_new.count() << " microseconds" << std::endl;
    std::cout << "Improvement: " << (duration_old.count() - duration_new.count()) * 100.0 / duration_old.count() << "%" << std::endl;
}
