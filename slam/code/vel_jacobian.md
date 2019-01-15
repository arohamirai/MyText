```
    Eigen::Matrix<double, 6, 6> vel_jacobian(Eigen::Affine3d aMb)
    {
        Eigen::Matrix<double, 6, 6> aVb;
        Eigen::Affine3d eMc = cMe.inverse();
        Eigen::Matrix3d aRb = aMb.rotation().matrix();
        Eigen::Vector3d aTb = aMb.translation();
        Eigen::Matrix3d aTb_cross;
        aTb_cross << 0, -aTb(2), aTb(1),
                aTb(2), 0, -aTb(0),
        -aTb(1), aTb(0), 0;
        aVb.setIdentity();
        aVb.block(0, 0, 3, 3) = aRb;
        aVb.block(0, 3, 3, 3) = aTb_cross * aTb;
        aVb.block(3, 3, 3, 3) = aRb;
        
        return aVb;
    }
```