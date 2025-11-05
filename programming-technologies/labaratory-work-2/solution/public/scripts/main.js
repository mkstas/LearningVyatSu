const productsElement = document.querySelector('.products');
const drawerElement = document.querySelector('.drawer');
const drawerBackButton = document.querySelector('.drawer__back-button');
const drawerListElement = document.querySelector('.drawer__list');
const drawerTotalValueElement = document.querySelector('.drawer__total-value');
const drawerCheckoutButton = document.querySelector('.drawer__checkout-button');
const headerCartButton = document.querySelector('.header__cart-button');
const paymentElement = document.querySelector('.payment');
const paymentForm = document.querySelector('.payment__form');
const closePaymentFormButton = document.querySelector('.payment__close-button');
const phoneNumberInput = document.querySelector('#phone_number');
const cardNumberInput = document.querySelector('#card_number');
const cvvCodeInput = document.querySelector('#cvv_code');

IMask(phoneNumberInput, { mask: '+{7} (000) 000 00 00' });
IMask(cardNumberInput, { mask: '0000 0000 0000 0000' });
IMask(cvvCodeInput, { mask: '000' });

headerCartButton.addEventListener('click', () => drawerElement.classList.toggle('drawer--active'));
drawerBackButton.addEventListener('click', () => drawerElement.classList.remove('drawer--active'));

drawerCheckoutButton.addEventListener('click', () => {
  paymentElement.classList.add('payment--active');
  document.body.classList.add('body--lock');
});

closePaymentFormButton.addEventListener('click', () => {
  paymentElement.classList.remove('payment--active');
  document.body.classList.remove('body--lock');
});

const getCart = () => {
  return JSON.parse(localStorage.getItem('cart')) ?? [];
};

const setCart = cart => {
  localStorage.setItem('cart', JSON.stringify(cart));
};

const getTotalCost = cart => {
  return cart.reduce((acc, item) => acc + item.price, 0);
};

const updateHeaderCartCost = () => {
  headerCartButton.querySelector('span').innerText = getTotalCost(getCart()) + ' руб.';
};

const updateTotalDrawerCost = () => {
  drawerTotalValueElement.innerText = getTotalCost(getCart()) + ' руб.';
};

updateHeaderCartCost();
updateTotalDrawerCost();

const checkAndDisableCheckoutButton = () => {
  if (getTotalCost(getCart()) === 0) {
    drawerCheckoutButton.disabled = true;
  } else {
    drawerCheckoutButton.disabled = false;
  }
};

checkAndDisableCheckoutButton();

const setCardButtonToAdd = button => {
  button.innerText = 'В корзину';
  button.classList.remove('button--outline');
};

const setCardButtonToDelete = button => {
  button.innerText = 'Удалить';
  button.classList.add('button--outline');
};

const updateCart = product => {
  const cart = getCart();
  const isInCart = !!cart.find(item => item.id === product.id);

  if (isInCart) {
    setCart(cart.filter(item => item.id !== product.id));
    setCardButtonToAdd(productsElement.querySelector(`[data-product-id="${product.id}"]`));
  }

  if (!isInCart) {
    cart.push(product);
    setCart(cart);
    setCardButtonToDelete(productsElement.querySelector(`[data-product-id="${product.id}"]`));
  }

  updateHeaderCartCost();
  updateTotalDrawerCost();
  checkAndDisableCheckoutButton();
};

const getProducts = async () => {
  try {
    const response = await fetch('/api/v1/products');
    const products = await response.json();

    return products;
  } catch (error) {
    console.error(error);
  }
};

const createCartProductElement = product => {
  return `
    <div class="drawer__item">
      <img class="drawer__item-image" src="${product.imageUrl}" alt="${product.title}" />
      <div class="drawer__item-info">
        <h3 class="drawer__item-title">${product.title}</h3>
        <p class="drawer__item-price">${product.price} руб.</p>
      </div>
      <button data-product-id=${product.id} class="drawer__item-remove">
        <img src="img/x-black.svg" alt="" />
      </button>
    </div>`;
};

const createProductElement = (product, cart) => {
  const isInCart = !!cart.find(item => item.id === product.id);

  return `
    <article class="card">
      <img src="${product.imageUrl}" alt="${product.title}" class="card__image" />
      <h3 class="card__title">${product.title}</h3>
      <div class="card__row">
        <span class="card__price">${product.price} руб.</span>
        <button data-product-id=${product.id} class="button${isInCart ? ' button--outline' : ''}">
          ${isInCart ? 'Убрать' : 'В корзину'}
        </button>
      </div>
    <article>`;
};

const displayCartProducts = () => {
  cart = getCart();
  drawerListElement.innerHTML = '';

  if (cart.length === 0) return;

  cart.forEach(product => {
    drawerListElement.innerHTML += createCartProductElement(product);
  });

  cart.forEach(product => {
    drawerListElement
      .querySelector(`[data-product-id="${product.id}"]`)
      .addEventListener('click', () => {
        updateCart(product);
        displayCartProducts();
      });
  });
};

displayCartProducts();

const displayProducts = async () => {
  const products = await getProducts();
  const cart = getCart();

  products.forEach(product => {
    productsElement.innerHTML += createProductElement(product, cart);
  });

  products.forEach(product => {
    productsElement
      .querySelector(`[data-product-id="${product.id}"]`)
      .addEventListener('click', () => {
        updateCart(product);
        displayCartProducts();
      });
  });
};

displayProducts();

paymentForm.addEventListener('submit', async e => {
  e.preventDefault();

  const formData = new FormData(e.target);
  const jsonData = Object.fromEntries(formData);
  jsonData.cart = getCart();

  try {
    const response = await fetch('/api/v1/orders', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(jsonData),
    });

    if (response.ok) {
      setCart([]);
      displayCartProducts();
      updateHeaderCartCost();
      updateTotalDrawerCost();

      paymentForm.reset();
      paymentElement.classList.remove('payment--active');
      drawerElement.classList.remove('drawer--active');
      productsElement.innerHTML = '';

      displayProducts();
    }
  } catch (error) {
    console.error(error);
  }
});
