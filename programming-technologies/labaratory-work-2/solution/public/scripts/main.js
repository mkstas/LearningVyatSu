const paymentForm = document.querySelector('#payment_form');
const paymentMethods = document.querySelectorAll('.payments__method');

const phoneNumberInput = document.querySelector('#phone_number');
const cardNumberInput = document.querySelector('#card_number');
const cvvInput = document.querySelector('#cvv');

IMask(phoneNumberInput, {
  mask: '+{7} (000) 000 00 00',
});

IMask(cardNumberInput, {
  mask: '0000 0000 0000 0000',
});

IMask(cvvInput, {
  mask: '000',
});

paymentForm.addEventListener('submit', async e => {
  e.preventDefault();

  const formData = new FormData(e.target);
  const jsonData = JSON.stringify(Object.fromEntries(formData));

  try {
    const response = await fetch('/api/v1/payments', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: jsonData,
    });

    if (response.ok) {
      paymentForm.reset();
    }
  } catch (error) {
    console.error('Network error:', error);
  }
});

paymentMethods.forEach(method => {
  method.addEventListener('click', function () {
    paymentMethods.forEach(m => m.classList.remove('selected'));

    method.classList.add('selected');
    method.querySelector('input[type="radio"]').checked = true;
  });
});
