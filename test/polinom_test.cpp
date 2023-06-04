#include <fstream>
#include "../lib/poli.h"
#include "../lib/mono.h"
#include "../gtest/gtest.h"
#include <string>


TEST(Monom_test, create_monom) {
    EXPECT_NO_THROW(monom());
}

TEST(Monom_test, create_monom_pow_error) {
    ASSERT_ANY_THROW(monom(5,powint/2,powint/2,powint/2 +1));
}
TEST(Monom_test, multiplicate_monom) {
    monom m1(5, 1, 1, 1);
    monom m2(5, 2, -1, 4);
    monom m3(25, 3, 0, 5);
    monom m4(24, 3, 1, 5);

    ASSERT_EQ(m1*m2==m3, true);
    ASSERT_EQ(m1 * m2 == m4, false);


}



TEST(Polinom_Test, create_polinom) {
    EXPECT_NO_THROW(polinom());
}
TEST(Polinom_Test, push_polinom) {
    polinom a;
    monom m1(5,5,5,5);

    EXPECT_NO_THROW(a.push(m1));
}
TEST(Polinom_Test, copy_polinom) {
    polinom p1;
    polinom p2;
    monom m1(1, 1, 1, 1);
    monom m2(2, 2, 2, 2);
    p1.push(m1);
    p1.push(m2);
    p2 = p1;
    ASSERT_EQ(p1==p2, true);
    p1.push(m1);
    ASSERT_NE(p1 == p2, true);
}

TEST(Polinom_Test, polinom_save_read_from_file) {
    polinom p1;
    monom m1(1, 1, 1, 1);
    monom m2(2, 2, 2, 2);
    p1.push(m1);
    p1.push(m2);
    p1.save("polinom.txt");
    polinom lfile;
    ifstream file("polinom.txt");
    file >> lfile;
    ASSERT_EQ(p1 == lfile, true);

}


TEST(Polinom_Test, polinom_sum) {
    polinom p1;
    monom m1(1, 1, 1, 1);
    monom m2(2, 2, 2, 2);
    p1.push(m1);
    p1.push(m2);
    polinom p2;
    monom m3(5, 1, 1, 1);
    monom m4(2, 3, 3, 3);
    p2.push(m3);
    p2.push(m4);
    polinom p3;
    p3 = p1 + p2;
    
    polinom p4;
    p4.push(monom(6, 1, 1, 1));
    p4.push(monom(2,2,2,2));
    p4.push(monom(2,3,3,3));



    ASSERT_EQ(p3==p4, true);
    ASSERT_EQ(p3 == p1, false);

}

TEST(Polinom_Test, create_big_polinom) {
    polinom p1;
    for (int i = 0;i < 100;i++) {
        monom m(1,i%5,i%6,1);
        p1.push(m);
    }
}

TEST(Polinom_Test, copy_big_polinom) {
    polinom p1;
    for (int i = 0;i < 100;i++) {
        EXPECT_NO_THROW(p1.push(monom(1,i%2,i%5,1)));
    }
    polinom p2;
    p2 = p1;
    ASSERT_EQ(p1 == p2, true);
    p1.push(monom(1, 1, 1, 1));
    ASSERT_EQ(p1 == p2, false);
}


TEST(Polinom_Test, big_polinom_sum) {
    polinom p1;
    monom m1(1, 1, 1, 1);
    monom m2(2, 2, 2, 2);
    p1.push(m1);
    p1.push(m2);
    polinom p2;
    monom m3(5, 1, 1, 1);
    monom m4(2, 3, 3, 3);
    p2.push(m3);
    p2.push(m4);
    polinom p3;
    p3 = p1 + p2;

    polinom p4;
    p4.push(monom(6, 1, 1, 1));
    p4.push(monom(2, 2, 2, 2));
    p4.push(monom(2, 3, 3, 3));



    ASSERT_EQ(p3 == p4, true);
    ASSERT_EQ(p3 == p1, false);
}


TEST(Polinom_Test, big_polinom_save_read_from_file) {
    polinom p1;
    monom m1(1, 1, 1, 1);
    monom m2(2, 2, 2, 2);
    p1.push(m1);
    p1.push(m2);
    p1.save("polinom.txt");
    polinom lfile;
    ifstream file("polinom.txt");
    file >> lfile;
    ASSERT_EQ(p1 == lfile, true);

}
