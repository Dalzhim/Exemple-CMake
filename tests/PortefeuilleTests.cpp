#include "gtest/gtest.h"
#include "lib_mini_banque/Portefeuille.h"

namespace {

	class PortefeuilleTest : public ::testing::Test {
	protected:
		Portefeuille pf;
	};

	TEST_F(PortefeuilleTest, TestDefaultConstructor) {
		EXPECT_EQ(pf.solde(), 0);
	}

	TEST_F(PortefeuilleTest, TestDepot) {
		EXPECT_EQ(pf.depot(20), 20);
		EXPECT_EQ(pf.solde(), 20);
	}

	TEST_F(PortefeuilleTest, TestRetrait) {
		pf.depot(30);
		EXPECT_EQ(pf.retrait(10), 20);
		EXPECT_EQ(pf.solde(), 20);
	}

	TEST_F(PortefeuilleTest, TestDepotNegatif) {
		auto solde = pf.solde();
		EXPECT_EQ(pf.depot(-10), solde);
		EXPECT_EQ(pf.solde(), solde);
	}

	TEST_F(PortefeuilleTest, TestRetraitNegatif) {
		auto solde = pf.solde();
		EXPECT_EQ(pf.retrait(-10), solde);
		EXPECT_EQ(pf.solde(), solde);
	}

	TEST_F(PortefeuilleTest, TestSoldeNegatif) {
		auto solde = pf.solde();
		EXPECT_EQ(pf.retrait(20), solde);
		EXPECT_EQ(pf.solde(), solde);
	}

	TEST_F(PortefeuilleTest, TestDepotCoupures) {
		auto solde = pf.solde();
		EXPECT_EQ(pf.depot(1), 0);
		EXPECT_EQ(pf.solde(), solde);
		EXPECT_EQ(pf.depot(2), 0);
		EXPECT_EQ(pf.solde(), solde);
		EXPECT_EQ(pf.depot(3), 0);
		EXPECT_EQ(pf.solde(), solde);
		EXPECT_EQ(pf.depot(4), 0);
		EXPECT_EQ(pf.solde(), solde);
		EXPECT_EQ(pf.depot(5), 5);
		EXPECT_EQ(pf.solde(), solde + 5);
		EXPECT_EQ(pf.depot(10), 15);
		EXPECT_EQ(pf.solde(), solde + 15);
		EXPECT_EQ(pf.depot(115), 130);
		EXPECT_EQ(pf.solde(), solde + 130);
	}

	TEST_F(PortefeuilleTest, TestRetraitCoupures) {
		pf.depot(200);
		auto solde = pf.solde();
		pf.retrait(1);
		EXPECT_EQ(pf.solde(), solde);
		pf.retrait(2);
		EXPECT_EQ(pf.solde(), solde);
		pf.retrait(3);
		EXPECT_EQ(pf.solde(), solde);
		pf.retrait(4);
		EXPECT_EQ(pf.solde(), solde);
		pf.retrait(5);
		EXPECT_EQ(pf.solde(), solde - 5);
		pf.retrait(10);
		EXPECT_EQ(pf.solde(), solde - 15);
		pf.retrait(115);
		EXPECT_EQ(pf.solde(), solde - 130);
	}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

