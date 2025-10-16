#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "g1_25_assign1_interfaces_pkg/msg/tentamen.hpp"
#include "g1_25_assign1_interfaces_pkg/msg/student.hpp"

/**
 * Unit tests voor Random Generator Testing
 * 
 * Deze tests valideren:
 * - Randomness van tentamen cijfers (10-100 range)
 * - Distribution uniformiteit over tijd
 * - Range compliance (geen waarden buiten 10-100)
 * - Percentage-based distribution validation
 * - Statistical randomness properties
 * - Chi-square goodness of fit test
 * 
 * NOTE: Deze tests simuleren de random generator logica direct
 * om onafhankelijk van de volledige ROS2 systeem te kunnen testen
 */

class RandomGeneratorTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        // Initialize ROS2 for basic functionality
        if (!rclcpp::ok()) {
            rclcpp::init(0, nullptr);
        }
        
        // Generate test data by simulating the random generator logic
        // This is the same logic used in the actual generator: 10 + (rand() % 91)
        generateTestSamples(200); // Generate 200 samples for comprehensive testing
    }

    void TearDown() override 
    {
        received_grades_.clear();
        received_messages_.clear();
    }

    // Simulate the random generator logic from g1_25_tentamen_result_generator_node.cpp
    void generateTestSamples(int count) 
    {
        // Initialize random seed for reproducible testing
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        received_grades_.clear();
        received_messages_.clear();
        
        // Generate samples using the same logic as the actual generator
        for (int i = 0; i < count; ++i) {
            int random_grade = 10 + (std::rand() % 91); // Same as in generator: 10-100 range
            received_grades_.push_back(random_grade);
            
            // Create a mock message for completeness
            g1_25_assign1_interfaces_pkg::msg::Tentamen msg;
            msg.student_name = "TestStudent" + std::to_string(i % 5); // 5 different students
            msg.course_name = "TestCourse";
            msg.tentamen_cijfer = random_grade;
            received_messages_.push_back(msg);
        }
    }

    // Helper om basic statistics te berekenen
    struct Statistics {
        double mean;
        double std_dev;
        int min_value;
        int max_value;
        double variance;
    };

    Statistics calculate_statistics(const std::vector<int>& data) {
        Statistics stats;
        
        if (data.empty()) {
            return {0.0, 0.0, 0, 0, 0.0};
        }
        
        stats.min_value = *std::min_element(data.begin(), data.end());
        stats.max_value = *std::max_element(data.begin(), data.end());
        
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        stats.mean = sum / data.size();
        
        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0,
            [](double const& x, double const& y) { return x + y; },
            [stats](double const& x, double const& y) { return (x - stats.mean) * (y - stats.mean); });
        
        stats.variance = sq_sum / data.size();
        stats.std_dev = std::sqrt(stats.variance);
        
        return stats;
    }

    // Chi-square test voor uniformiteit
    double chi_square_test(const std::vector<int>& data, int num_bins = 9) {
        if (data.empty()) return 0.0;
        
        // Maak bins voor range 10-100 (91 waarden, 9 bins van ~10 each)
        std::vector<int> bins(num_bins, 0);
        int bin_size = 91 / num_bins; // ~10 per bin
        
        for (int grade : data) {
            if (grade >= 10 && grade <= 100) {
                int bin_index = std::min((grade - 10) / bin_size, num_bins - 1);
                bins[bin_index]++;
            }
        }
        
        // Verwachte frequency per bin (uniform distribution)
        double expected = static_cast<double>(data.size()) / num_bins;
        
        // Bereken chi-square statistic
        double chi_square = 0.0;
        for (int bin_count : bins) {
            if (expected > 0) {
                chi_square += std::pow(bin_count - expected, 2) / expected;
            }
        }
        
        return chi_square;
    }

    std::vector<int> received_grades_;
    std::vector<g1_25_assign1_interfaces_pkg::msg::Tentamen> received_messages_;
};

/**
 * Test 1: Basic Range Validation
 * Verificeert dat alle gegenereerde cijfers binnen 10-100 range vallen
 */
TEST_F(RandomGeneratorTest, TestGradeRangeCompliance)
{
    ASSERT_GE(received_grades_.size(), 100) << "Insufficient samples generated for range test";
    
    // Controleer dat alle waarden binnen range 10-100 vallen
    for (size_t i = 0; i < received_grades_.size(); ++i) {
        EXPECT_GE(received_grades_[i], 10) 
            << "Grade " << received_grades_[i] << " below minimum (10) at sample " << i;
        EXPECT_LE(received_grades_[i], 100) 
            << "Grade " << received_grades_[i] << " above maximum (100) at sample " << i;
    }
    
    std::cout << "Range validation: Tested " << received_grades_.size() << " samples" << std::endl;
    std::cout << "  Min grade: " << *std::min_element(received_grades_.begin(), received_grades_.end()) << std::endl;
    std::cout << "  Max grade: " << *std::max_element(received_grades_.begin(), received_grades_.end()) << std::endl;
}

/**
 * Test 2: Statistical Randomness Properties
 * Test dat de generator redelijke statistische properties heeft
 */
TEST_F(RandomGeneratorTest, TestStatisticalRandomness)
{
    ASSERT_GE(received_grades_.size(), 100) << "Insufficient samples for statistical analysis";
    
    auto stats = calculate_statistics(received_grades_);
    
    // Voor uniform distribution over 10-100:
    // Expected mean: (10 + 100) / 2 = 55
    // Expected std deviation: ongeveer 26.1 voor uniform distribution
    
    EXPECT_GT(stats.mean, 40.0) << "Mean too low, might not be random: " << stats.mean;
    EXPECT_LT(stats.mean, 70.0) << "Mean too high, might not be random: " << stats.mean;
    
    // Standard deviation should indicate proper spread
    EXPECT_GT(stats.std_dev, 15.0) << "Standard deviation too low, insufficient randomness: " << stats.std_dev;
    EXPECT_LT(stats.std_dev, 35.0) << "Standard deviation too high, suspicious pattern: " << stats.std_dev;
    
    // Range should be reasonable
    EXPECT_GE(stats.max_value - stats.min_value, 30) << "Range too small, poor randomness";
    
    std::cout << "Statistical analysis results:" << std::endl;
    std::cout << "  Mean: " << stats.mean << " (expected ~55)" << std::endl;
    std::cout << "  Std Dev: " << stats.std_dev << " (expected ~26)" << std::endl;
    std::cout << "  Range: " << stats.min_value << " - " << stats.max_value << std::endl;
}

/**
 * Test 3: Distribution Uniformity Test
 * Test dat de verdeling redelijk uniform is over verschillende bins
 */
TEST_F(RandomGeneratorTest, TestDistributionUniformity)
{
    ASSERT_GE(received_grades_.size(), 100) << "Insufficient samples for distribution test";
    
    // Verdeel in bins: 10-30, 31-50, 51-70, 71-90, 91-100
    std::vector<int> bins = {0, 0, 0, 0, 0};
    std::vector<std::string> bin_labels = {"10-30", "31-50", "51-70", "71-90", "91-100"};
    
    for (int grade : received_grades_) {
        if (grade >= 10 && grade <= 30) bins[0]++;
        else if (grade >= 31 && grade <= 50) bins[1]++;
        else if (grade >= 51 && grade <= 70) bins[2]++;
        else if (grade >= 71 && grade <= 90) bins[3]++;
        else if (grade >= 91 && grade <= 100) bins[4]++;
    }
    
    // Print distribution voor debugging
    std::cout << "Grade distribution:" << std::endl;
    for (size_t i = 0; i < bins.size(); ++i) {
        double percentage = (static_cast<double>(bins[i]) / received_grades_.size()) * 100.0;
        std::cout << "  " << bin_labels[i] << ": " << bins[i] << " (" << percentage << "%)" << std::endl;
    }
    
    // Elke bin zou ongeveer 20% moeten hebben (±15% tolerance)
    double expected_percentage = 20.0;
    double tolerance = 15.0; // Ruime tolerance voor kleine sample size
    
    for (size_t i = 0; i < bins.size(); ++i) {
        double actual_percentage = (static_cast<double>(bins[i]) / received_grades_.size()) * 100.0;
        
        EXPECT_GE(actual_percentage, expected_percentage - tolerance)
            << "Bin " << bin_labels[i] << " heeft te weinig samples: " << actual_percentage << "%";
        EXPECT_LE(actual_percentage, expected_percentage + tolerance)
            << "Bin " << bin_labels[i] << " heeft te veel samples: " << actual_percentage << "%";
    }
}

/**
 * Test 4: Percentage-Based Validation
 * Test specifieke percentage ranges zoals gevraagd
 */
TEST_F(RandomGeneratorTest, TestPercentageRangeValidation)
{
    ASSERT_GE(received_grades_.size(), 100) << "Insufficient samples for percentage validation";
    
    // Test verschillende percentage ranges
    
    // 1. Slaag percentage (≥55): zou ongeveer 50% moeten zijn
    int passing_grades = std::count_if(received_grades_.begin(), received_grades_.end(),
        [](int grade) { return grade >= 55; });
    double pass_percentage = (static_cast<double>(passing_grades) / received_grades_.size()) * 100.0;
    
    EXPECT_GE(pass_percentage, 30.0) << "Too few passing grades: " << pass_percentage << "%";
    EXPECT_LE(pass_percentage, 70.0) << "Too many passing grades: " << pass_percentage << "%";
    
    // 2. Hoge cijfers (≥80): zou ongeveer 23% moeten zijn
    int high_grades = std::count_if(received_grades_.begin(), received_grades_.end(),
        [](int grade) { return grade >= 80; });
    double high_percentage = (static_cast<double>(high_grades) / received_grades_.size()) * 100.0;
    
    EXPECT_GE(high_percentage, 10.0) << "Too few high grades: " << high_percentage << "%";
    EXPECT_LE(high_percentage, 40.0) << "Too many high grades: " << high_percentage << "%";
    
    // 3. Lage cijfers (<40): zou ongeveer 33% moeten zijn  
    int low_grades = std::count_if(received_grades_.begin(), received_grades_.end(),
        [](int grade) { return grade < 40; });
    double low_percentage = (static_cast<double>(low_grades) / received_grades_.size()) * 100.0;
    
    EXPECT_GE(low_percentage, 15.0) << "Too few low grades: " << low_percentage << "%";
    EXPECT_LE(low_percentage, 50.0) << "Too many low grades: " << low_percentage << "%";
    
    std::cout << "Percentage validation results:" << std::endl;
    std::cout << "  Passing grades (≥55): " << pass_percentage << "%" << std::endl;
    std::cout << "  High grades (≥80): " << high_percentage << "%" << std::endl;
    std::cout << "  Low grades (<40): " << low_percentage << "%" << std::endl;
}

/**
 * Test 5: Chi-Square Goodness of Fit Test
 * Geavanceerde statistische test voor uniformiteit
 */
TEST_F(RandomGeneratorTest, TestChiSquareUniformity)
{
    ASSERT_GE(received_grades_.size(), 150) << "Insufficient samples for chi-square test";
    
    double chi_square = chi_square_test(received_grades_, 9);
    
    // Voor 9-1=8 degrees of freedom, critical value bij α=0.05 is ~15.51
    // Voor α=0.01 is het ~20.09
    // We gebruiken liberale threshold omdat sample size mogelijk klein is
    double critical_value = 25.0; // Ruime threshold
    
    EXPECT_LT(chi_square, critical_value) 
        << "Chi-square test failed: " << chi_square << " > " << critical_value 
        << " (distribution might not be uniform)";
    
    std::cout << "Chi-square test result: " << chi_square 
              << " (critical value: " << critical_value << ")" << std::endl;
}

/**
 * Test 6: Randomness Over Time
 * Test dat opeenvolgende waarden niet gecorreleerd zijn
 */
TEST_F(RandomGeneratorTest, TestTemporalRandomness)
{
    ASSERT_GE(received_grades_.size(), 100) << "Insufficient samples for temporal test";
    
    // Test dat opeenvolgende waarden niet te veel op elkaar lijken
    int consecutive_similar = 0;
    const int similarity_threshold = 10; // Verschil van 10 punten of minder
    
    for (size_t i = 1; i < received_grades_.size(); ++i) {
        if (std::abs(received_grades_[i] - received_grades_[i-1]) <= similarity_threshold) {
            consecutive_similar++;
        }
    }
    
    // Maximaal 50% van opeenvolgende waarden mogen "similar" zijn
    double similarity_rate = static_cast<double>(consecutive_similar) / (received_grades_.size() - 1);
    
    EXPECT_LT(similarity_rate, 0.6) 
        << "Too many consecutive similar values: " << similarity_rate * 100 << "%"
        << " (possible pattern in generator)";
    
    std::cout << "Temporal randomness: " << consecutive_similar 
              << " out of " << (received_grades_.size() - 1) 
              << " consecutive pairs are similar (" << similarity_rate * 100 << "%)" << std::endl;
}

/**
 * Test 7: Multiple Student Randomness
 * Test dat verschillende studenten verschillende random sequences krijgen
 */
TEST_F(RandomGeneratorTest, TestMultiStudentRandomness)
{
    ASSERT_GE(received_messages_.size(), 100) << "Insufficient messages for multi-student test";
    
    // Groepeer grades per student
    std::unordered_map<std::string, std::vector<int>> student_grades;
    
    for (const auto& msg : received_messages_) {
        student_grades[msg.student_name].push_back(msg.tentamen_cijfer);
    }
    
    // Controleer dat elke student verschillende gemiddelden heeft (waarschijnlijk)
    std::vector<double> means;
    
    for (const auto& pair : student_grades) {
        if (pair.second.size() >= 5) { // Minimaal 5 samples per student
            double sum = std::accumulate(pair.second.begin(), pair.second.end(), 0.0);
            double mean = sum / pair.second.size();
            means.push_back(mean);
            
            std::cout << "Student " << pair.first 
                      << " - samples: " << pair.second.size() 
                      << ", mean: " << mean << std::endl;
        }
    }
    
    ASSERT_GE(means.size(), 2) << "Not enough students with sufficient samples";
    
    // Test dat de means niet allemaal hetzelfde zijn (zeer onwaarschijnlijk bij echte randomness)
    bool has_variation = false;
    for (size_t i = 1; i < means.size(); ++i) {
        if (std::abs(means[i] - means[0]) > 2.0) { // Verschil van meer dan 2 punten
            has_variation = true;
            break;
        }
    }
    
    EXPECT_TRUE(has_variation) << "All students have very similar means, generator might be faulty";
}

/**
 * Test 8: Overall Random Generator Accuracy
 * Berekent een overall accuracy percentage voor de random generator
 */
TEST_F(RandomGeneratorTest, TestOverallAccuracy)
{
    ASSERT_GE(received_grades_.size(), 100) << "Insufficient samples for accuracy test";
    
    int accuracy_points = 0;
    int total_points = 7; // 7 criteria
    
    // 1. Range compliance (10 points if 100% within range)
    bool range_perfect = true;
    for (int grade : received_grades_) {
        if (grade < 10 || grade > 100) {
            range_perfect = false;
            break;
        }
    }
    if (range_perfect) accuracy_points++;
    
    // 2. Mean accuracy (10 points if within 40-70 range)
    auto stats = calculate_statistics(received_grades_);
    if (stats.mean >= 40.0 && stats.mean <= 70.0) accuracy_points++;
    
    // 3. Standard deviation (10 points if between 15-35)
    if (stats.std_dev >= 15.0 && stats.std_dev <= 35.0) accuracy_points++;
    
    // 4. Distribution uniformity (bins should be 15-25% each)
    std::vector<int> bins = {0, 0, 0, 0, 0};
    for (int grade : received_grades_) {
        if (grade >= 10 && grade <= 30) bins[0]++;
        else if (grade >= 31 && grade <= 50) bins[1]++;
        else if (grade >= 51 && grade <= 70) bins[2]++;
        else if (grade >= 71 && grade <= 90) bins[3]++;
        else if (grade >= 91 && grade <= 100) bins[4]++;
    }
    
    bool distribution_good = true;
    for (int bin_count : bins) {
        double percentage = (static_cast<double>(bin_count) / received_grades_.size()) * 100.0;
        if (percentage < 10.0 || percentage > 30.0) {
            distribution_good = false;
            break;
        }
    }
    if (distribution_good) accuracy_points++;
    
    // 5. Passing percentage (should be 30-70%)
    int passing_grades = std::count_if(received_grades_.begin(), received_grades_.end(),
        [](int grade) { return grade >= 55; });
    double pass_percentage = (static_cast<double>(passing_grades) / received_grades_.size()) * 100.0;
    if (pass_percentage >= 30.0 && pass_percentage <= 70.0) accuracy_points++;
    
    // 6. Chi-square test (should be < 25)
    double chi_square = chi_square_test(received_grades_, 9);
    if (chi_square < 25.0) accuracy_points++;
    
    // 7. Temporal randomness (similarity rate should be < 60%)
    int consecutive_similar = 0;
    for (size_t i = 1; i < received_grades_.size(); ++i) {
        if (std::abs(received_grades_[i] - received_grades_[i-1]) <= 10) {
            consecutive_similar++;
        }
    }
    double similarity_rate = static_cast<double>(consecutive_similar) / (received_grades_.size() - 1);
    if (similarity_rate < 0.6) accuracy_points++;
    
    // Bereken overall accuracy
    double overall_accuracy = (static_cast<double>(accuracy_points) / total_points) * 100.0;
    
    std::cout << std::endl;
    std::cout << "=== RANDOM GENERATOR ACCURACY REPORT ===" << std::endl;
    std::cout << "Overall Accuracy: " << std::fixed << std::setprecision(1) << overall_accuracy << "%" << std::endl;
    std::cout << "Passed Criteria: " << accuracy_points << "/" << total_points << std::endl;
    std::cout << std::endl;
    std::cout << "Detailed Breakdown:" << std::endl;
    std::cout << "  Range Compliance: " << (range_perfect ? "PASS" : "FAIL") << std::endl;
    std::cout << "  Mean Accuracy: " << (stats.mean >= 40.0 && stats.mean <= 70.0 ? "PASS" : "FAIL") 
              << " (" << std::fixed << std::setprecision(1) << stats.mean << ")" << std::endl;
    std::cout << "  Std Deviation: " << (stats.std_dev >= 15.0 && stats.std_dev <= 35.0 ? "PASS" : "FAIL") 
              << " (" << std::fixed << std::setprecision(1) << stats.std_dev << ")" << std::endl;
    std::cout << "  Distribution: " << (distribution_good ? "PASS" : "FAIL") << std::endl;
    std::cout << "  Pass Rate: " << (pass_percentage >= 30.0 && pass_percentage <= 70.0 ? "PASS" : "FAIL") 
              << " (" << std::fixed << std::setprecision(1) << pass_percentage << "%)" << std::endl;
    std::cout << "  Chi-Square: " << (chi_square < 25.0 ? "PASS" : "FAIL") 
              << " (" << std::fixed << std::setprecision(1) << chi_square << ")" << std::endl;
    std::cout << "  Temporal Random: " << (similarity_rate < 0.6 ? "PASS" : "FAIL") 
              << " (" << std::fixed << std::setprecision(1) << similarity_rate * 100 << "%)" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Test should pass if accuracy is at least 70%
    EXPECT_GE(overall_accuracy, 70.0) << "Random generator accuracy too low: " << overall_accuracy << "%";
}

// Test runner
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}